#pragma once
#include "../Macros.h"

#include <JuceHeader.h>
#include "SerializableProjectStructure.h"

namespace vocalshaper {
	class VSAPI Wave : public SerializableProjectStructure
	{
	public:
		Wave()
			:SerializableProjectStructure(SerializableProjectStructure::Type::Wave)
		{};
		~Wave() override = default;

	private:
		friend class ProjectDAO;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Wave)
	};
}
