#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "ProjectEventStructure.h"
#include "../datas/Json.h"

namespace vocalshaper {
	class VSAPI JsonEvent : public ProjectEventStructure
	{
	public:
		JsonEvent(ProjectEventStructure::ChangeType cType)
			:ProjectEventStructure(ProjectEventStructure::Type::Json, cType)
		{};
		~JsonEvent() override = default;

		struct Target {
			int addition;
		};

		void setTarget(Target target);
		const Target getTarget() const;

	private:
		friend class EventUndo;
		Target target;

	private:
		JUCE_LEAK_DETECTOR(JsonEvent)
	};
}