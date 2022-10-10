﻿#include "TempoTemp.h"
#include "LabelTemp.h"

#include <cmath>

namespace vocalshaper {
	TempoTemp::TempoTemp(LabelTemp* labels)
		:labels(labels)
	{};

	void TempoTemp::refresh()
	{
		if (!this->labels) {
			return;
		}

		juce::ScopedWriteLock locker1(this->lock);
		juce::ScopedReadLock locker2(this->labels->lock);

		//清空缓存
		this->list.clear();

		//上一标签状态缓存
		double temp_te = 0.;

		//计算曲速缓存
		for (int i = 0; i < this->labels->list.size(); i++) {
			auto& currentLabel = this->labels->list.getReference(i);

			double xs = 0, xe = 0, ts = 0, te = 0, Ts = 0, Te = 0, delta = 0;

			if (i < this->labels->list.size() - 1) {
				//非最后标签
				auto& nextLabel = this->labels->list.getReference(i + 1);
				if (currentLabel.autoTempo && (currentLabel.tempo != nextLabel.tempo)) {
					//TypeB
					xs = currentLabel.x;
					xe = nextLabel.x;
					Ts = currentLabel.tempo;
					Te = nextLabel.tempo;
					delta = TempoTemp::typeB_delta(xs, xe, Ts, Te);
					ts = temp_te;
					te = temp_te = TempoTemp::typeB_t(xe, xs, Ts, delta, ts);
				}
				else {
					//TypeA
					xs = currentLabel.x;
					xe = nextLabel.x;
					Ts = currentLabel.tempo;
					Te = Ts;
					delta = 0.;
					ts = temp_te;
					te = temp_te = TempoTemp::typeA_t(xe, xs, Ts, ts);
				}
			}
			else {
				//最后标签
				xs = currentLabel.x;
				xe = DBL_MAX;
				Ts = currentLabel.tempo;
				Te = Ts;
				delta = 0.;
				ts = temp_te;
				te = temp_te = DBL_MAX;
			}

			//添加缓存
			this->list.add({
						.xs = xs,
						.xe = xe,
						.ts = ts,
						.te = te,
						.Ts = Ts,
						.Te = Te,
						.delta = delta
				});
		}
	}

	double TempoTemp::get_x(double t) const
	{
		juce::ScopedReadLock locker(this->lock);

		int index = this->selectLabelBy_t(t);
		return this->get_x(t, index);
	}

	double TempoTemp::get_t(double x) const
	{
		juce::ScopedReadLock locker(this->lock);

		int index = this->selectLabelBy_x(x);
		return this->get_t(x, index);
	}

	double TempoTemp::get_T(double x) const
	{
		juce::ScopedReadLock locker(this->lock);

		int index = this->selectLabelBy_x(x);
		return this->get_T(x, index);
	}

	double TempoTemp::get_x(double t, int index) const
	{
		juce::ScopedReadLock locker(this->lock);

		auto& temp = this->list.getReference(index);
		if (!(t >= temp.ts && t < temp.te)) {
			return 0;
		}

		if (temp.delta == 0.) {
			//TypeA
			return TempoTemp::typeA_x(t, temp.ts, temp.Ts, temp.xs);
		}
		else {
			//TypeB
			return TempoTemp::typeB_x(t, temp.ts, temp.Ts, temp.delta, temp.xs);
		}
	}

	double TempoTemp::get_t(double x, int index) const
	{
		juce::ScopedReadLock locker(this->lock);

		auto& temp = this->list.getReference(index);
		if (!(x >= temp.xs && x < temp.xe)) {
			return 0;
		}

		if (temp.delta == 0.) {
			//TypeA
			return TempoTemp::typeA_t(x, temp.xs, temp.Ts, temp.ts);
		}
		else {
			//TypeB
			return TempoTemp::typeB_t(x, temp.xs, temp.Ts, temp.delta, temp.ts);
		}
	}

	double TempoTemp::get_T(double x, int index) const
	{
		juce::ScopedReadLock locker(this->lock);

		auto& temp = this->list.getReference(index);
		if (!(x >= temp.xs && x < temp.xe)) {
			return 0.;
		}

		if (temp.delta == 0.) {
			//TypeA
			return temp.Ts;
		}
		else {
			//TypeB
			return TempoTemp::typeB_T(x, temp.xs, temp.delta, temp.Ts);
		}
	}

	int TempoTemp::selectLabelBy_x(double x) const
	{
		juce::ScopedReadLock locker(this->lock);

		for (int i = 0; i < this->list.size(); i++) {
			auto& current = this->list.getReference(i);
			if (x >= current.xs && x < current.xe) {
				return i;
			}
		}
		return this->list.size() - 1;
	}

	int TempoTemp::selectLabelBy_t(double t) const
	{
		juce::ScopedReadLock locker(this->lock);

		for (int i = 0; i < this->list.size(); i++) {
			auto& current = this->list.getReference(i);
			if (t >= current.ts && t < current.te) {
				return i;
			}
		}
		return this->list.size() - 1;
	}

	//关于x-t映射函数的数学推导详见文档
	double TempoTemp::typeA_t(double x, double xs, double Ts, double ts)
	{
		//t(x) = ((x - xs) / Ts) * 60 + ts
		return ((x - xs) / Ts) * 60. + ts;
	}

	double TempoTemp::typeA_x(double t, double ts, double Ts, double xs)
	{
		//x(t) = ((t - ts) / 60) * Ts + xs
		return ((t - ts) / 60.) * Ts + xs;
	}

	double TempoTemp::typeB_delta(double xs, double xe, double Ts, double Te)
	{
		//δ = (Te - Ts) / (xe - xs)
		return (Te - Ts) / (xe - xs);
	}

	double TempoTemp::typeB_T(double x, double xs, double delta, double Ts)
	{
		//T(x) = (x - xs) * delta + Ts
		return (x - xs) * delta + Ts;
	}

	double TempoTemp::typeB_t(double x, double xs, double Ts, double delta, double ts)
	{
		//t(x) = (ln((delta * (x - xs) + Ts) / Ts) / delta) * 60 + ts
		return (std::log((delta * (x - xs) + Ts) / Ts) / delta) * 60. + ts;
	}

	double TempoTemp::typeB_x(double t, double ts, double Ts, double delta, double xs)
	{
		//x(t) = (Ts * e ^ (delta * ((t - ts) / 60)) - Ts) / delta + xs
		return (Ts * std::exp(delta * ((t - ts) / 60.)) - Ts) / delta + xs;
	}
}