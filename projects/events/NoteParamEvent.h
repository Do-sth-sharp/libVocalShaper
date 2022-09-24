#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "ProjectEventStructure.h"
#include "../datas/Param.h"

namespace vocalshaper {
	class VSAPI NoteParamEvent : public ProjectEventStructure
	{
	public:
		NoteParamEvent(ProjectEventStructure::ChangeType cType)
			:ProjectEventStructure(ProjectEventStructure::Type::NoteParam, cType)
		{};
		~NoteParamEvent() override = default;

		struct Target {
			int track;
			int note;
			int param;
		};

		void setTarget(Target target);
		const Target getTarget() const;

	private:
		friend class EventUndo;
		Target target;

	private:
		JUCE_LEAK_DETECTOR(NoteParamEvent)
	};
}