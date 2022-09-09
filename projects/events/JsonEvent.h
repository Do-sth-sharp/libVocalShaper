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

		void setPtr(Json* ptr);
		Json* getPtr() const;
		void setTarget(Target target);
		const Target getTarget() const;

	private:
		friend class ProjectMerger;
		std::unique_ptr<Json> ptr1, ptr2;
		Target target;

	private:
		JUCE_LEAK_DETECTOR(JsonEvent)
	};
}