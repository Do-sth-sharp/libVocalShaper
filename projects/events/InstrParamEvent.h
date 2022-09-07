#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "ProjectEventStructure.h"
#include "../datas/Param.h"

namespace vocalshaper {
	class VSAPI InstrParamEvent : public ProjectEventStructure
	{
	public:
		InstrParamEvent(ProjectEventStructure::ChangeType cType)
			:ProjectEventStructure(ProjectEventStructure::Type::InstrParam, cType)
		{};
		~InstrParamEvent() override;

		struct Target {
			int track;
			int param;
		};

	private:
		std::unique_ptr<Param> ptr1, ptr2;
		Target target;

	private:
		JUCE_LEAK_DETECTOR(InstrParamEvent)
	};
}