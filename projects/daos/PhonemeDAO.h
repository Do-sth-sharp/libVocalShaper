#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "../datas/Phoneme.h"
#include "PointDAO.h"

namespace vocalshaper {
	class VSAPI PhonemeDAO
	{
		PhonemeDAO() = default;

	public:
		static uint32_t getDeviation(const Phoneme* ptr);
		static void setDeviation(Phoneme* ptr, uint32_t deviation);
		static juce::String getName(const Phoneme* ptr);
		static void setName(Phoneme* ptr, juce::String name);
		static bool getIsPre(const Phoneme* ptr);
		static void setIsPre(Phoneme* ptr, bool isPre);

		static int timePointSize(const Phoneme* ptr);
		static Point* getTimePoint(const Phoneme* ptr, int index);
		static Point* insertTimePoint(Phoneme* ptr, int index, Point* point);
		static Point* releaseTimePoint(Phoneme* ptr, int index);

	public:
		static bool isSaved(const Phoneme* ptr);
		static void save(Phoneme* ptr);

	public:
		static Phoneme* create();
		static void destory(Phoneme* ptr);
	};
}