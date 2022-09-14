#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "ProjectEventStructure.h"
#include "../datas/Project.h"

namespace vocalshaper {
	class VSAPI ProjectEvent : public ProjectEventStructure
	{
	public:
		ProjectEvent(ProjectEventStructure::ChangeType cType)
			:ProjectEventStructure(ProjectEventStructure::Type::Project, cType)
		{};
		~ProjectEvent() override;

		struct Target {
		};

		void setTarget(Target target);
		const Target getTarget() const;

	private:
		friend class EventUndo;
		Target target;

	private:
		JUCE_LEAK_DETECTOR(ProjectEvent)
	};
}