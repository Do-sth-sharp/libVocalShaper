#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "ProjectEventStructure.h"
#include "../datas/Curve.h"

namespace vocalshaper {
	class VSAPI CurveEvent : public ProjectEventStructure
	{
	public:
		CurveEvent(ProjectEventStructure::ChangeType cType)
			:ProjectEventStructure(ProjectEventStructure::Type::Curve, cType)
		{};
		~CurveEvent() override;

		struct Target {
			int track;
			int curve;
		};

	private:
		std::unique_ptr<Curve> ptr1, ptr2;
		Target target;

	private:
		JUCE_LEAK_DETECTOR(CurveEvent)
	};
}