#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>

namespace vocalshaper {
	class VSAPI LabelTemp;

	class VSAPI BeatTemp final
	{
	public:
		explicit BeatTemp(LabelTemp* labels);
		~BeatTemp() = default;

		struct BeatData final {
			double xInQuarter = 0;	//位置，以四分音符记
			double xInBar = 0;		//位置，以小节记
			uint8_t beat = 4;		//拍号
			uint8_t base = 4;		//拍基
		};

		//由标签缓存刷新节拍缓存
		void refresh();

		//从缓存获取数据
		uint8_t getBeatAtTime(double x) const;
		uint8_t getBaseAtTime(double x) const;
		double getBarAtTime(double x) const;
		double getTimeAtBar(double bar) const;

		int selectBy_x(double x) const;
		int selectBy_bar(double bar) const;

	private:
		juce::Array<BeatData> list;
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

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BeatTemp)
	};
}