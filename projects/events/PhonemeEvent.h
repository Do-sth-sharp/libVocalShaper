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

		void setPtr(Phoneme* ptr);
		Phoneme* getPtr() const;
		void setTarget(Target target);
		const Target getTarget() const;

	private:
		friend class ProjectMerger;
		std::unique_ptr<Phoneme> ptr1, ptr2;
		Target target;

	private:
		JUCE_LEAK_DETECTOR(PhonemeEvent)
	};
}