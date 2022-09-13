#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "ProjectEventStructure.h"
#include "../datas/Track.h"

namespace vocalshaper {
	class VSAPI TrackEvent : public ProjectEventStructure
	{
	public:
		TrackEvent(ProjectEventStructure::ChangeType cType)
			:ProjectEventStructure(ProjectEventStructure::Type::Track, cType)
		{};
		~TrackEvent() override;

		struct Target {
			int track;
		};

		void setTarget(Target target);
		const Target getTarget() const;

	private:
		Target target;

	private:
		JUCE_LEAK_DETECTOR(TrackEvent)
	};
}