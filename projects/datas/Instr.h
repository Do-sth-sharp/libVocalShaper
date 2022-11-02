#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "SerializableProjectStructure.h"
#include "Param.h"

namespace vocalshaper {
	class VSAPI Instr : public SerializableProjectStructure
	{
	public:
		enum class InstrType {
			Unknown,
			VST,
			VST3,
			AU,
			LADSPA
		}instrType = InstrType::Unknown;					//乐器类型

	public:
		Instr(InstrType type)
			:SerializableProjectStructure(SerializableProjectStructure::Type::Instr),
			instrType(type)
		{};

	private:
		int uniqueId = 0;									//乐器唯一标识

		juce::OwnedArray<Param> params;						//参数

	private:
		friend class InstrDAO;
		friend class ProjectCopier;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Instr)
	};
}
