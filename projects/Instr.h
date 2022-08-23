#pragma once
#include "../Macros.h"

#include <JuceHeader.h>
#include "SerializableProjectStructure.h"

namespace vocalshaper {
	class VSAPI Instr : public SerializableProjectStructure
	{
	public:
		Instr()
			:SerializableProjectStructure(SerializableProjectStructure::Type::Instr)
		{};
		~Instr() override = default;

	private:
		friend class ProjectDAO;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Instr)
	};
}
