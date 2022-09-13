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

		void setTarget(Target target);
		const Target getTarget() const;

	private:
		Target target;

	private:
		JUCE_LEAK_DETECTOR(InstrParamEvent)
	};
}