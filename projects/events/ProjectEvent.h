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

		void setPtr(Project* ptr);
		Project* getPtr() const;
		void setTarget(Target target);
		const Target getTarget() const;

	private:
		std::unique_ptr<Project> ptr1, ptr2;
		Target target;

	private:
		JUCE_LEAK_DETECTOR(ProjectEvent)
	};
}