#pragma once
#include "../Macros.h"

#include <JuceHeader.h>
#include "SerializableProjectStructure.h"
#include "Utils.h"

namespace vocalshaper {
	class VSAPI DPoint : public SerializableProjectStructure
	{
	public:
		DPoint()
			:SerializableProjectStructure(SerializableProjectStructure::Type::DPoint)
		{};
		~DPoint() override = default;

	private:
		ProjectTime x = make_time(0, 0);								//时间
		double y = 0;													//值
		double dl = 0, dr = 0;											//左右导数

	private:
		friend class ProjectDAO;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DPoint)
	};
}
