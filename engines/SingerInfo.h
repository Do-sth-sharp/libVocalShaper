#pragma once
#include "../Macros.h"
#include <JuceHeader.h>

namespace vocalshaper {
	class VSAPI SingerInfo final
	{
	public:
		juce::String id;								//声库id（与模块名相同）
		juce::String name;								//声库显示名称
		juce::Colour color;								//代表色
		juce::String portrait;							//立绘路径
		juce::StringArray styles;						//样式列表（首个样式为默认样式）
		std::tuple<juce::String, juce::String> engine;	//引擎id和最低版本要求
		juce::StringArray languages;					//语言列表
		juce::String description;						//声库简介
		juce::String license;							//许可协议
	};
}