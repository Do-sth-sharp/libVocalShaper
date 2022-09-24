#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "ProjectEventStructure.h"
#include "../datas/Wave.h"

namespace vocalshaper {
	class VSAPI WaveEvent : public ProjectEventStructure
	{
	public:
		WaveEvent(ProjectEventStructure::ChangeType cType)
			:ProjectEventStructure(ProjectEventStructure::Type::Wave, cType)
		{};
		~WaveEvent() override = default;

		struct Target {
			int track;
			int wave;
		};

		void setTarget(Target target);
		const Target getTarget() const;

	private:
		friend class EventUndo;
		Target target;

	private:
		JUCE_LEAK_DETECTOR(WaveEvent)
	};
}