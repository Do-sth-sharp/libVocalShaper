﻿#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "SerializableProjectStructure.h"

namespace vocalshaper {
	class VSAPI Point : public SerializableProjectStructure
	{
	public:
		Point()
			:SerializableProjectStructure(SerializableProjectStructure::Type::Point)
		{};

	private:
		double x = 0;
		double y = 0;

	private:
		friend class PointDAO;
		friend class ProjectCopier;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Point)
	};
}
