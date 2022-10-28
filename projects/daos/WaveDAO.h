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
		static double getDeviation(const Wave* ptr);
		static void setDeviation(Wave* ptr, double deviation);
		static double getSt(const Wave* ptr);
		static void setSt(Wave* ptr, double time);
		static double getLength(const Wave* ptr);
		static void setLength(Wave* ptr, double length);

	public:
		static bool isSaved(const Wave* ptr);
		static void save(Wave* ptr);
	};
}