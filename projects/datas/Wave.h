#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "SerializableProjectStructure.h"

namespace vocalshaper {
	class VSAPI Wave : public SerializableProjectStructure
	{
	public:
		Wave()
			:SerializableProjectStructure(SerializableProjectStructure::Type::Wave)
		{};

	private:
		juce::String source;				//音频源
		double deviation = 0;				//起始位置相较源偏移

		double st = 0;						//起始时间
		double length = 0;					//长度

	private:
		friend class WaveDAO;
		friend class ProjectCopier;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Wave)
	};
}
