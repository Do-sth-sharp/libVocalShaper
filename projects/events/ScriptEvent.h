#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "ProjectEventStructure.h"
#include "../datas/Script.h"

namespace vocalshaper {
	class VSAPI ScriptEvent : public ProjectEventStructure
	{
	public:
		ScriptEvent(ProjectEventStructure::ChangeType cType)
			:ProjectEventStructure(ProjectEventStructure::Type::Script, cType)
		{};
		~ScriptEvent() override;

		struct Target {
			int script;
		};

		void setTarget(Target target);
		const Target getTarget() const;

	private:
		Target target;

	private:
		JUCE_LEAK_DETECTOR(ScriptEvent)
	};
}