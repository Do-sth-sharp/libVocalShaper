#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "ProjectEventStructure.h"
#include "../datas/Wave.h"

namespace vocalshaper {
	class VSAPI WaveEvent : public ProjectEventStructure
	{
	public:
		WaveEvent(ProjectEventStructure::ChangeType cType)
			:ProjectEventStructure(ProjectEventStructure::Type::Wave, cType)
		{};
		~WaveEvent() override;

		struct Target {
			int track;
			int wave;
		};

		void setPtr(Wave* ptr);
		Wave* getPtr() const;
		void setTarget(Target target);
		const Target getTarget() const;

	private:
		friend class ProjectMerger;
		std::unique_ptr<Wave> ptr1, ptr2;
		Target target;

	private:
		JUCE_LEAK_DETECTOR(WaveEvent)
	};
}