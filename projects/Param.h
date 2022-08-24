#pragma once
#include "../Macros.h"

#include <JuceHeader.h>
#include "SerializableProjectStructure.h"

namespace vocalshaper {
	class VSAPI Param : public SerializableProjectStructure
	{
	public:
		Param()
			:SerializableProjectStructure(SerializableProjectStructure::Type::Param)
		{};
		~Param() override = default;

		enum class ParamType {
			Empty,
			Bool,
			Choice,
			Float,
			Int
		}paramType = ParamType::Empty;		//参数类型

	private:
		juce::String id;					//唯一id
		union Value {
			bool boolData;
			int choiceData;
			float floatData;
			int intData;
		}value;								//值

		juce::String controler;				//连接至控制器

	private:
		friend class ProjectDAO;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Param)
	};
}
