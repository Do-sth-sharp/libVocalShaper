#pragma once
#include "../Macros.h"
#include <JuceHeader.h>
#include "RendererBase.h"
#include "SpliterBase.h"
#include "PhoneratorBase.h"
#include "ParamInfo.h"

namespace vocalshaper {
	//所有引擎的共同基类，继承此类并重写接口实现引擎
	//每个引擎实例将被固定的附加于一条歌声轨道，并伴随歌声轨道的整个生命周期直到轨道模式改变或声库改变
	class VSAPI EngineBase
	{
	public:
		EngineBase() = default;
		virtual ~EngineBase() = default;

		//渲染模式，决定当前引擎渲染时机
		enum class RenderMode
		{
			AOT = 0x01,			//预渲染，渲染在项目数据更改发生时执行
			JIT = 0x02,			//实时渲染，渲染在播放时进行，渲染进度保持在领先于播放进度的位置
			Both = AOT | JIT	//两个模式同时进行
		};

		//引擎配置符号表
		struct EngineFlags
		{
			bool renderPitch : 1 = false;			//引擎主动渲染音高曲线
			bool exportSpectrogrum : 1 = false;		//引擎在渲染音频的同时导出语谱图
		};

		//重写此方法返回当前引擎的符号表
		//引擎符号表决定了引擎具有哪些基础功能
		virtual const EngineFlags getEngineFlags() const = 0;

		//重写此方法返回当前引擎的显示名称
		//VocalShaper不会依赖该名称区分引擎种类，但要确保其人类可辨认性
		virtual const juce::String getEngineShortName() const = 0;

		//重写此方法返回当前引擎的渲染模式
		//引擎托盘将根据该返回值决定调用渲染器的时机
		virtual const RenderMode getRenderMode() const = 0;

		//重写此方法返回当前引擎的参数列表
		//在引擎加载时被调用
		virtual const ParamInfoList getParamList() const = 0;


		//重写此方法返回当前引擎实例的渲染器指针
		//渲染器指针指向的内存应由当前引擎自行管理，并确保该内存不会先于引擎实例释放
		virtual RendererBase const* getRenderer() const = 0;

		//重写此方法返回当前引擎实例的分句器指针
		//分句器指针指向的内存应由当前引擎自行管理，并确保该内存不会先于引擎实例释放
		virtual SpliterBase const* getSpliter() const = 0;

		//重写此方法返回当前引擎实例的音素器指针
		//音素器指针指向的内存应由当前引擎自行管理，并确保该内存不会先于引擎实例释放
		virtual PhoneratorBase const* getPhonerator() const = 0;

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EngineBase)
	};
}