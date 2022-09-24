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
		~CurveEvent() override = default;

		struct Target {
			int track;
			int curve;
		};

		void setTarget(Target target);
		const Target getTarget() const;

	private:
		friend class EventUndo;
		Target target;

	private:
		JUCE_LEAK_DETECTOR(CurveEvent)
	};
}