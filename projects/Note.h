#pragma once
#include "../Macros.h"

#include <JuceHeader.h>
#include "SerializableProjectStructure.h"

namespace vocalshaper {
	class VSAPI Note : public SerializableProjectStructure
	{
	public:
		Note()
			:SerializableProjectStructure(SerializableProjectStructure::Type::Note)
		{};
		~Note() override = default;

	private:
		friend class ProjectDAO;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Note)
	};
}
