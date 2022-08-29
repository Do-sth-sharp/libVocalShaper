#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "SerializableProjectStructure.h"

namespace vocalshaper {
	class VSAPI Script : public SerializableProjectStructure
	{
	public:
		Script()
			:SerializableProjectStructure(SerializableProjectStructure::Type::Script)
		{};
		~Script() override = default;

		enum class ScriptType {
			Lua,
			Js,
			AIL
		}scriptType = ScriptType::Lua;		//脚本类型

	private:
		juce::String data;					//脚本数据
		bool enabled = true;				//脚本生效

	private:
		friend class ScriptDAO;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Script)
	};
}
