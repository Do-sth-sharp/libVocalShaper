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

	private:
		std::unique_ptr<Track> ptr1, ptr2;
		Target target;

	private:
		JUCE_LEAK_DETECTOR(TrackEvent)
	};
}