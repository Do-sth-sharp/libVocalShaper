#pragma once
#include "../Macros.h"

#include <JuceHeader.h>
#include "SerializableProjectStructure.h"

namespace vocalshaper {
	class VSAPI DPoint : public SerializableProjectStructure
	{
	public:
		DPoint()
			:SerializableProjectStructure(SerializableProjectStructure::Type::DPoint)
		{};
		~DPoint() override = default;

	private:
		friend class ProjectDAO;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DPoint)
	};
}
