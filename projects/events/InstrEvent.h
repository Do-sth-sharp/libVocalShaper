#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "ProjectEventStructure.h"
#include "../datas/Instr.h"

namespace vocalshaper {
	class VSAPI InstrEvent : public ProjectEventStructure
	{
	public:
		InstrEvent(ProjectEventStructure::ChangeType cType)
			:ProjectEventStructure(ProjectEventStructure::Type::Instr, cType)
		{};
		~InstrEvent() override;

		struct Target {
			int track;
		};

		void setPtr(Instr* ptr);
		Instr* getPtr() const;
		void setTarget(Target target);
		const Target getTarget() const;

	private:
		std::unique_ptr<Instr> ptr1, ptr2;
		Target target;

	private:
		JUCE_LEAK_DETECTOR(InstrEvent)
	};
}