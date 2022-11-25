#pragma once
#include "../Macros.h"
#include <JuceHeader.h>
#include "PhonemeInfo.h"
#include "../projects/datas/Track.h"

namespace vocalshaper {
	//Phonerator: Phoneme Generator，音素生成器，音素器
	//音素器：根据轨道设置与音符信息生成音符所对应的音素标记序列
	//所有引擎音素器的共同基类，继承此类并重写接口实现引擎音素器
	class VSAPI PhoneratorBase
	{
	public:
		PhoneratorBase() = default;
		virtual ~PhoneratorBase() = default;

		//重写此方法返回音素列表
		//传入参数
		//track: 指向当前轨道的指针，其类型必然为歌声轨，可以从其中获取音符与声库相关的信息
		//noteIndex: 当前要解析的音符索引，注意此时轨道中的相应音符的音素状态为未更新的状态
		//currentSentence: 当前音符所属分句的起止音符序号，序号为闭区间
		//返回值
		//返回当前音符的音素列表更新后的状态，按偏移量由小到大排列
		virtual const PhonemeInfoListWithDeviation getPhoneme(
			const Track* track, int noteIndex, const std::tuple<int, int> currentSentence) const = 0;

		//重写此方法根据声库与样式返回所有支持的音素列表
		virtual const PhonemeInfoList getAllPhonemesForSinger(
			const juce::String& singer, const juce::String& style) const = 0;

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhoneratorBase)
	};
}