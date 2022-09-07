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
		~NoteParamEvent() override;

		struct Target {
			int track;
			int note;
			int param;
		};

	private:
		std::unique_ptr<Param> ptr1, ptr2;
		Target target;

	private:
		JUCE_LEAK_DETECTOR(NoteParamEvent)
	};
}