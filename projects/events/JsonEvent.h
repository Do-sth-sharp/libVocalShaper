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
		~JsonEvent() override;

		struct Target {
			int addition;
		};

	private:
		std::unique_ptr<Json> ptr1, ptr2;
		Target target;

	private:
		JUCE_LEAK_DETECTOR(JsonEvent)
	};
}