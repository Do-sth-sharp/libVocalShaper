#pragma once
#include "../Macros.h"

#include <JuceHeader.h>
#include "SerializableProjectStructure.h"

namespace vocalshaper {
	class VSAPI Track : public SerializableProjectStructure
	{
	public:
		Track()
			:SerializableProjectStructure(SerializableProjectStructure::Type::Track)
		{};
		~Track() override = default;

	private:
		friend class ProjectDAO;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Track)
	};
}
