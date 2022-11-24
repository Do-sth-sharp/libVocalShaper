#pragma once
#include "../Macros.h"
#include <JuceHeader.h>

namespace vocalshaper {
	//渲染器：根据轨道数据生成音频片段
	//所有引擎渲染器的共同基类，继承此类并重写接口实现引擎渲染器
	class VSAPI RendererBase
	{
	public:
		RendererBase() = default;
		virtual ~RendererBase() = default;

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RendererBase)
	};
}