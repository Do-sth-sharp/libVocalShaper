#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "SerializableProjectStructure.h"
#include "Utils.h"

namespace vocalshaper {
	class VSAPI Wave : public SerializableProjectStructure
	{
	public:
		Wave()
			:SerializableProjectStructure(SerializableProjectStructure::Type::Wave)
		{};
		~Wave() override = default;

	private:
		juce::String source;									//音频源
		uint64_t deviation = 0;									//起始位置相较源偏移

		ProjectTime st = make_time(0, 0);						//起始时间
		uint32_t length = 0;									//长度

	private:
		friend class WaveDAO;
		friend class ProjectCopier;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Wave)
	};
}
