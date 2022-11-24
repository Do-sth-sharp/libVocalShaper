#pragma once
#include "../Macros.h"
#include <JuceHeader.h>

namespace vocalshaper {
	//Phonerator: Phoneme Generator，音素生成器，音素器
	//音素器：根据轨道设置与音符信息生成音符所对应的音素标记序列
	//所有引擎音素器的共同基类，继承此类并重写接口实现引擎音素器
	class VSAPI PhoneratorBase
	{
	public:
		PhoneratorBase() = default;
		virtual ~PhoneratorBase() = default;

		

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhoneratorBase)
	};
}