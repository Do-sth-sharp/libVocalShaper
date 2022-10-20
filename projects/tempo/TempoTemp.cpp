#include "TempoTemp.h"
#include "LabelTemp.h"

#include <cmath>

namespace vocalshaper {
	TempoTemp::TempoTemp(LabelTemp* labels)
		:labels(labels)
	{
		this->list.add(TempoData());
	};

	void TempoTemp::refresh()
	{
		if (!this->labels) {
			return;
		}

		juce::ScopedWriteLock locker1(this->lock);
		juce::ScopedReadLock locker2(this->labels->lock);

		//清空缓存
		this->list.clear();
		this->lastIndex = 0;

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

		//取出缓存的块
		auto& tempBlock = this->list.getReference(this->lastIndex);

		//如果时间在当前与下一块之间，缓存命中
		if ((x >= tempBlock.xs) && (x < tempBlock.xe)) {
			return this->lastIndex;
		}

		//缓存命中下一块
		if (this->lastIndex < this->list.size() - 1) {
			auto& nextBlock = this->list.getReference(this->lastIndex + 1);
			if ((x >= nextBlock.xs) && (x < nextBlock.xe)) {
				return ++(this->lastIndex);
			}
		}

		//查找比较函数
		auto CFunc = [](double x, const TempoData& curr)->CompareResult {
			if (x >= curr.xs && x < curr.xe) {
				return CompareResult::EQ;
			}
			else if (x >= curr.xe) {
				return CompareResult::GTR;
			}
			else {
				return CompareResult::LSS;
			}
		};

		//缓存未命中，判断缓存在当前之前还是之后
		if (x < tempBlock.xs) {
			//之前

			//二分查找
			return this->lastIndex = this->search(0, this->lastIndex, x, CFunc);
		}
		else {
			//之后

			//二分查找
			return this->lastIndex = this->search(this->lastIndex, this->list.size() - 1, x, CFunc);
		}
	}

	int TempoTemp::selectLabelBy_t(double t) const
	{
		juce::ScopedReadLock locker(this->lock);

		//取出缓存的块
		auto& tempBlock = this->list.getReference(this->lastIndex);

		//如果时间在当前与下一块之间，缓存命中
		if ((t >= tempBlock.ts) && (t < tempBlock.te)) {
			return this->lastIndex;
		}

		//缓存命中下一块
		if (this->lastIndex < this->list.size() - 1) {
			auto& nextBlock = this->list.getReference(this->lastIndex + 1);
			if ((t >= nextBlock.ts) && (t < nextBlock.te)) {
				return ++(this->lastIndex);
			}
		}

		//查找比较函数
		auto CFunc = [](double t, const TempoData& curr)->CompareResult {
			if (t >= curr.ts && t < curr.te) {
				return CompareResult::EQ;
			}
			else if (t >= curr.te) {
				return CompareResult::GTR;
			}
			else {
				return CompareResult::LSS;
			}
		};

		//缓存未命中，判断缓存在当前之前还是之后
		if (t < tempBlock.ts) {
			//之前

			//二分查找
			return this->lastIndex = this->search(0, this->lastIndex, t, CFunc);
		}
		else {
			//之后

			//二分查找
			return this->lastIndex = this->search(this->lastIndex, this->list.size() - 1, t, CFunc);
		}
	}

	template<typename Func, typename T>
	int TempoTemp::search(int low, int high, T value, Func func) const
	{
		int mid = (low + high) / 2;
		if (func(value, this->list.getReference(mid)) == CompareResult::EQ) {
			return mid;
		}
		else if (func(value, this->list.getReference(mid)) == CompareResult::GTR) {
			return this->search(mid, high, value, func);
		}
		else {
			return this->search(low, mid, value, func);
		}
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