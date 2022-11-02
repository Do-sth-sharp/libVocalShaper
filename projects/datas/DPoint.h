#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "SerializableProjectStructure.h"

namespace vocalshaper {
	class VSAPI DPoint : public SerializableProjectStructure
	{
	public:
		DPoint()
			:SerializableProjectStructure(SerializableProjectStructure::Type::DPoint)
		{};

	private:
		double x = 0;								//时间
		double y = 0;								//值
		double dl = 0, dr = 0;						//左右导数

	private:
		friend class DPointDAO;
		friend class ProjectCopier;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DPoint)
	};
}
