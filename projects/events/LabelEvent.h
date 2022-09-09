#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "ProjectEventStructure.h"
#include "../datas/Label.h"

namespace vocalshaper {
	class VSAPI LabelEvent : public ProjectEventStructure
	{
	public:
		LabelEvent(ProjectEventStructure::ChangeType cType)
			:ProjectEventStructure(ProjectEventStructure::Type::Label, cType)
		{};
		~LabelEvent() override;

		struct Target {
			int label;
		};

		void setPtr(Label* ptr);
		Label* getPtr() const;
		void setTarget(Target target);
		const Target getTarget() const;

	private:
		friend class ProjectMerger;
		std::unique_ptr<Label> ptr1, ptr2;
		Target target;

	private:
		JUCE_LEAK_DETECTOR(LabelEvent)
	};
}