#pragma once
#include "../Macros.h"

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

	private:
		friend class ProjectDAO;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Script)
	};
}
