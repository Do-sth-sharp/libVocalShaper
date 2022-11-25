#pragma once
#include "../Macros.h"
#include <JuceHeader.h>

namespace vocalshaper {
	//分句器：将一个轨道上的音符划分为不同句，以区分更改发生时重渲染范围
	//所有引擎分句器的共同基类，继承此类并重写接口实现引擎分句器
	class VSAPI SpliterBase
	{
	public:
		SpliterBase() = default;
		virtual ~SpliterBase() = default;

		//乐句列表
		using SentenceList = juce::Array<std::tuple<int, int>>;

		//重写此方法返回当前轨道的乐句列表
		//传入参数为当前轨道的指针，其类型必然为歌声轨，注意其中音符的音素信息不一定为最新信息，应以歌词为准
		//返回各乐句的索引区间列表，该列表按顺序由小到大排列，区间为闭区间
		virtual const SentenceList getSentence(const Track* track) const = 0;

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SpliterBase)
	};
}