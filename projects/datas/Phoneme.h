#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "SerializableProjectStructure.h"
#include "Point.h"

namespace vocalshaper {
	class VSAPI Phoneme : public SerializableProjectStructure
	{
	public:
		Phoneme()
			:SerializableProjectStructure(SerializableProjectStructure::Type::Phoneme)
		{};
		~Phoneme() override = default;

	private:
		uint32_t deviation = 0;				//较音符起始位置偏移
		juce::String name = "a";			//音素名
		bool isPre = false;					//先导音素

		juce::OwnedArray<Point> timeMap;	//时间映射

	private:
		friend class PhonemeDAO;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Phoneme)
	};
}
