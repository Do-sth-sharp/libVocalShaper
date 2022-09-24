#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "SerializableProjectStructure.h"

namespace vocalshaper {
	class VSAPI Param : public SerializableProjectStructure
	{
	public:

		enum class ParamType {
			Empty,
			Bool,
			Choice,
			Float,
			Int
		}paramType = ParamType::Empty;		//参数类型

	public:
		Param(ParamType type)
			:SerializableProjectStructure(SerializableProjectStructure::Type::Param),
			paramType(type)
		{};
		~Param() override = default;

	private:
		juce::String id;					//唯一id
		union Value {
			bool boolData;
			int choiceData;
			float floatData;
			int intData;
		}value = { .intData = 0 };			//值

		juce::String controler;				//连接至控制器

	private:
		friend class ParamDAO;
		friend class ProjectCopier;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Param)
	};
}
