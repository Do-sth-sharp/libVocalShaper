#pragma once
#include "../Macros.h"
#include <JuceHeader.h>

namespace vocalshaper {
	//参数信息：描述某一个参数的固有属性
	struct VSAPI ParamInfo
	{
		//参数类型
		enum class ParamType
		{
			Static = 0x00,	//静态参数，附加于轨道中的音符作为音符属性，不随时间变化
			Dynamic = 0x01	//动态参数，附加于轨道，可以通过曲线控制
		};

		ParamType type = ParamType::Static;	//参数类型，决定参数的附加位置
		juce::String id;					//参数id，应确保当前引擎内参数id不会重复
		juce::String shortName;				//参数显示名称，不会依赖于该名称区分参数，但要确保人类可辨认性
		double minValue = 0.;				//参数的最小值，ui以此为依据确定显示范围下边界
		double maxValue = 1.;				//参数的最大值，ui以此为依据确定显示范围上边界
		double defaultValue = .5;			//参数的缺省值，如果当前关注范围内该参数未得到有效控制，则默认为该值
		bool allowOverflow = false;			//允许参数值超越最大值与最小值边界而不被限制
	};

	//参数信息列表
	using ParamInfoList = juce::Array<ParamInfo>;
}