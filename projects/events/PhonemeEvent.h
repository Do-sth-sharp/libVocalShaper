#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "ProjectEventStructure.h"
#include "../datas/Phoneme.h"

namespace vocalshaper {
	class VSAPI PhonemeEvent : public ProjectEventStructure
	{
	public:
		PhonemeEvent(ProjectEventStructure::ChangeType cType)
			:ProjectEventStructure(ProjectEventStructure::Type::Phoneme, cType)
		{};
		~PhonemeEvent() override;

		struct Target {
			int track;
			int note;
			int phoneme;
		};

		void setTarget(Target target);
		const Target getTarget() const;

	private:
		Target target;

	private:
		JUCE_LEAK_DETECTOR(PhonemeEvent)
	};
}