#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "ProjectEventStructure.h"
#include "../datas/Track.h"

namespace vocalshaper {
	class VSAPI MasterTrackEvent : public ProjectEventStructure
	{
	public:
		MasterTrackEvent(ProjectEventStructure::ChangeType cType)
			:ProjectEventStructure(ProjectEventStructure::Type::MasterTrack, cType)
		{};
		~MasterTrackEvent() override;

		struct Target {
		};

		void setTarget(Target target);
		const Target getTarget() const;

	private:
		Target target;

	private:
		JUCE_LEAK_DETECTOR(MasterTrackEvent)
	};
}