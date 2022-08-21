#pragma once
#include "../Macros.h"

#include <JuceHeader.h>
#include "SerializableProjectStructure.h"

namespace vocalshaper {
	class VSAPI Point : public SerializableProjectStructure
	{
	public:
		Point()
			:SerializableProjectStructure(SerializableProjectStructure::Type::Point)
		{};
		~Point() override = default;

	private:
		friend class ProjectDAO;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Point)
	};
}
