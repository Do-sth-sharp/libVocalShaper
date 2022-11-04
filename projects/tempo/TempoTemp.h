#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>

namespace vocalshaper {
	class VSAPI LabelTemp;

	class VSAPI TempoTemp final
	{
	public:
		explicit TempoTemp(LabelTemp* labels);
		~TempoTemp() = default;

		struct TempoData final {
			double xs = 0, xe = 0;
			double ts = 0, te = 0;
			double Ts = 120., Te = 120.;
			double delta = 0;
		};

		//由标签缓存刷新曲速缓存
		void refresh();

		//从缓存获取数据
		double get_x(double t) const;
		double get_t(double x) const;
		double get_T(double x) const;

		double get_x(double t, int index) const;
		double get_t(double x, int index) const;
		double get_T(double x, int index) const;

		int selectLabelBy_x(double x) const;
		int selectLabelBy_t(double t) const;

		const TempoData getTempData(int index) const;

	private:
		juce::Array<TempoData> list;
		juce::ReadWriteLock lock;

		LabelTemp* labels = nullptr;

		//使用后向缓存加速遍历
		mutable int lastIndex = 0;

		enum class CompareResult {
			EQ,
			GTR,
			LSS
		};
		template<typename Func, typename T>
		int search(int low, int high, T value, Func func) const;

	public:
		inline static double typeA_t(double x, double xs, double Ts, double ts);
		inline static double typeA_x(double t, double ts, double Ts, double xs);

		inline static double typeB_delta(double xs, double xe, double Ts, double Te);
		inline static double typeB_T(double x, double xs, double delta, double Ts);
		inline static double typeB_t(double x, double xs, double Ts, double delta, double ts);
		inline static double typeB_x(double t, double ts, double Ts, double delta, double xs);
	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TempoTemp)
	};
}