#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "SerializableProjectStructure.h"
#include "Utils.h"

namespace vocalshaper {
	class VSAPI Label : public SerializableProjectStructure
	{
	public:
		Label()
			:SerializableProjectStructure(SerializableProjectStructure::Type::Label)
		{};
		~Label() override = default;

		enum class LabelType {
			Lua,
			Ini,
			Xml,
			Json
		}labelType = LabelType::Lua;					//标签数据类型

	private:
		ProjectTime position = make_time(0, 0);			//标签位置
		juce::String data;								//标签内容

		/*
		* 标签内容规则
		* beat = 4			#设置节拍
		* tempo = 120		#设置曲速
		* autoTempo = false	#曲速自动过渡
		*/

	private:
		friend class LabelDAO;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Label)
	};
}
