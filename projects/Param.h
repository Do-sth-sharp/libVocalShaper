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

	private:
		friend class ProjectDAO;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Param)
	};
}
