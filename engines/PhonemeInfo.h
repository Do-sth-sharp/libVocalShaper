#pragma once
#include "../Macros.h"
#include <JuceHeader.h>

namespace vocalshaper {
	//音素信息
	struct VSAPI PhonemeInfo
	{
		//当前音素名称
		juce::String name;

		//音素类型
		//具体类型标准见文档
		juce::String type = "SLI";
	};

	//带偏移量的音素信息列表
	using PhonemeInfoListWithDeviation = juce::Array<std::tuple<double, PhonemeInfo>>;

	//音素信息列表
	using PhonemeInfoList = juce::Array<PhonemeInfo>;
}