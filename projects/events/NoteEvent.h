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

		void setPtr(Note* ptr);
		Note* getPtr() const;
		void setTarget(Target target);
		const Target getTarget() const;

	private:
		friend class ProjectMerger;
		std::unique_ptr<Note> ptr1, ptr2;
		Target target;

	private:
		JUCE_LEAK_DETECTOR(NoteEvent)
	};
}