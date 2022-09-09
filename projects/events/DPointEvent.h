#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "ProjectEventStructure.h"
#include "../datas/DPoint.h"

namespace vocalshaper {
	class VSAPI DPointEvent : public ProjectEventStructure
	{
	public:
		DPointEvent(ProjectEventStructure::ChangeType cType)
			:ProjectEventStructure(ProjectEventStructure::Type::DPoint, cType)
		{};
		~DPointEvent() override;

		struct Target {
			int track;
			int curve;
			int point;
		};

		void setPtr(DPoint* ptr);
		DPoint* getPtr() const;
		void setTarget(Target target);
		const Target getTarget() const;

	private:
		friend class ProjectMerger;
		std::unique_ptr<DPoint> ptr1, ptr2;
		Target target;

	private:
		JUCE_LEAK_DETECTOR(DPointEvent)
	};
}