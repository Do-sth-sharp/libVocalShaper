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

		void setPtr(Track* ptr);
		Track* getPtr() const;
		void setTarget(Target target);
		const Target getTarget() const;

	private:
		friend class ProjectMerger;
		std::unique_ptr<Track> ptr1, ptr2;
		Target target;

	private:
		JUCE_LEAK_DETECTOR(MasterTrackEvent)
	};
}