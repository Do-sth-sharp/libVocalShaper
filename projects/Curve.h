#pragma once
#include "../Macros.h"

#include <JuceHeader.h>
#include "SerializableProjectStructure.h"
#include "DPoint.h"

namespace vocalshaper {
	class VSAPI Curve : public SerializableProjectStructure
	{
	public:
		Curve()
			:SerializableProjectStructure(SerializableProjectStructure::Type::Curve)
		{};
		~Curve() override = default;

	private:

	private:
		friend class ProjectDAO;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Curve)
	};
}
