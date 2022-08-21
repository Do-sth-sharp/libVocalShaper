#pragma once
#include "../Macros.h"

#include <JuceHeader.h>
#include "SerializableProjectStructure.h"

namespace vocalshaper {
	class VSAPI Plugin : public SerializableProjectStructure
	{
	public:
		Plugin()
			:SerializableProjectStructure(SerializableProjectStructure::Type::Plugin)
		{};
		~Plugin() override = default;

	private:
		friend class ProjectDAO;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Plugin)
	};
}
