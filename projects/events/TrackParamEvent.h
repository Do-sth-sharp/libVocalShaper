#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "ProjectEventStructure.h"
#include "../datas/Param.h"

namespace vocalshaper {
	class VSAPI TrackParamEvent : public ProjectEventStructure
	{
	public:
		TrackParamEvent(ProjectEventStructure::ChangeType cType)
			:ProjectEventStructure(ProjectEventStructure::Type::TrackParam, cType)
		{};
		~TrackParamEvent() override;

		struct Target {
			int track;
			int param;
		};

		void setTarget(Target target);
		const Target getTarget() const;

	private:
		friend class EventUndo;
		Target target;

	private:
		JUCE_LEAK_DETECTOR(TrackParamEvent)
	};
}