#pragma once
#include "../../Macros.h"

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

	private:
		juce::String id;								//唯一id
		juce::OwnedArray<DPoint> points;				//控制点
		
	private:
		friend class CurveDAO;
		friend class ProjectCopier;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Curve)
	};
}
