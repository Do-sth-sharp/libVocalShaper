#pragma once
#include "../Macros.h"

#include <JuceHeader.h>
#include "SerializableProjectStructure.h"

namespace vocalshaper {
	class VSAPI Project : public SerializableProjectStructure
	{
	public:
		Project()
			:SerializableProjectStructure(SerializableProjectStructure::Type::Project)
		{};
		~Project() override = default;

	private:
		friend class ProjectDAO;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Project)
	};
}
