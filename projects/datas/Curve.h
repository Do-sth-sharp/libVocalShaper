﻿#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "SerializableProjectStructure.h"
#include "DPoint.h"

namespace vocalshaper {
	class VSAPI Curve : public SerializableProjectStructure
	{
	public:
		Curve()
			:SerializableProjectStructure(SerializableProjectStructure::Type::Curve)
		{};
		~Curve() override = default;

	private:
		juce::OwnedArray<DPoint> points;				//控制点
		
	private:
		friend class CurveDAO;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Curve)
	};
}