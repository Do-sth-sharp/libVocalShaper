#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "SerializableProjectStructure.h"

namespace vocalshaper {
	class VSAPI Label : public SerializableProjectStructure
	{
	public:
		Label()
			:SerializableProjectStructure(SerializableProjectStructure::Type::Label)
		{};

		enum class LabelType {
			Lua,
			Ini,
			Xml,
			Json
		}labelType = LabelType::Lua;					//标签数据类型

	private:
		double position = 0;			//标签位置
		juce::String data;				//标签内容

		/*
		* 标签内容规则
		* 1. Lua
		* beat = 4			--设置节拍
		* tempo = 120.00	--设置曲速
		* auto = false		--曲速自动过渡
		* 
		* 2. Ini
		* [Label]
		* beat = 4			#设置节拍
		* tempo = 120.00	#设置曲速
		* auto = false		#曲速自动过渡
		* 
		* 3. Xml
		* <label beat="4" tempo="120.00" auto="false"/>
		* 
		* 4. Json
		* {
		*	"beat": 4,
		*	"tempo": 120.00.
		*	"auto": false
		* }
		*/

	private:
		friend class LabelDAO;
		friend class ProjectCopier;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Label)
	};
}
