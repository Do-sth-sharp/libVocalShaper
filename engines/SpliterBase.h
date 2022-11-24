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

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SpliterBase)
	};
}