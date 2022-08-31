#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "../datas/Wave.h"

namespace vocalshaper {
	class VSAPI WaveDAO
	{
		WaveDAO() = default;

	public:
		static juce::String getSource(const Wave* ptr);
		static void setSource(Wave* ptr, juce::String source);
		static uint64_t getDeviation(const Wave* ptr);
		static void setDeviation(Wave* ptr, uint64_t deviation);
		static ProjectTime getSt(const Wave* ptr);
		static void setSt(Wave* ptr, ProjectTime time);
		static uint32_t getLength(const Wave* ptr);
		static void setLength(Wave* ptr, uint32_t length);

	public:
		static bool isSaved(const Wave* ptr);
		static void save(Wave* ptr);

	public:
		static Wave* create();
		static void destory(Wave* ptr);
	};
}