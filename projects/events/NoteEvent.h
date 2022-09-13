#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "ProjectEventStructure.h"
#include "../datas/Note.h"

namespace vocalshaper {
	class VSAPI NoteEvent : public ProjectEventStructure
	{
	public:
		NoteEvent(ProjectEventStructure::ChangeType cType)
			:ProjectEventStructure(ProjectEventStructure::Type::Note, cType)
		{};
		~NoteEvent() override;

		struct Target {
			int track;
			int note;
		};

		void setTarget(Target target);
		const Target getTarget() const;

	private:
		Target target;

	private:
		JUCE_LEAK_DETECTOR(NoteEvent)
	};
}