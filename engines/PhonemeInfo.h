#pragma once
#include "../Macros.h"
#include <JuceHeader.h>

namespace vocalshaper {
	//音素信息
	struct VSAPI PhonemeInfo
	{
		double deviation = 0;		//当前音素相对于音符头的偏移量，单位秒
		juce::String name;			//当前音素名称

		//音素类型
		//
		juce::String type = "SLI";
	};

	//音素信息列表
	using PhonemeInfoList = juce::Array<PhonemeInfo>;
}