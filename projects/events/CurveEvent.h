#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "ProjectEventStructure.h"
#include "../datas/Curve.h"

namespace vocalshaper {
	class VSAPI CurveEvent : public ProjectEventStructure
	{
	public:
		CurveEvent(ProjectEventStructure::ChangeType cType)
			:ProjectEventStructure(ProjectEventStructure::Type::Curve, cType)
		{};
		~CurveEvent() override;

		struct Target {
			int track;
			int curve;
		};

		void setPtr(Curve* ptr);
		Curve* getPtr() const;
		void setTarget(Target target);
		const Target getTarget() const;

	private:
		std::unique_ptr<Curve> ptr1, ptr2;
		Target target;

	private:
		JUCE_LEAK_DETECTOR(CurveEvent)
	};
}