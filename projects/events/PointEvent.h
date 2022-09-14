#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "ProjectEventStructure.h"
#include "../datas/Point.h"

namespace vocalshaper {
	class VSAPI PointEvent : public ProjectEventStructure
	{
	public:
		PointEvent(ProjectEventStructure::ChangeType cType)
			:ProjectEventStructure(ProjectEventStructure::Type::Point, cType)
		{};
		~PointEvent() override;

		struct Target {
			int track;
			int note;
			int phoneme;
			int point;
		};

		void setTarget(Target target);
		const Target getTarget() const;

	private:
		friend class EventUndo;
		Target target;

	private:
		JUCE_LEAK_DETECTOR(PointEvent)
	};
}