#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "ProjectEventStructure.h"
#include "../datas/DPoint.h"

namespace vocalshaper {
	class VSAPI DPointEvent : public ProjectEventStructure
	{
	public:
		DPointEvent(ProjectEventStructure::ChangeType cType)
			:ProjectEventStructure(ProjectEventStructure::Type::DPoint, cType)
		{};
		~DPointEvent() override = default;

		struct Target {
			int track;
			int curve;
			int point;
		};

		void setTarget(Target target);
		const Target getTarget() const;

	private:
		friend class EventUndo;
		Target target;

	private:
		JUCE_LEAK_DETECTOR(DPointEvent)
	};
}