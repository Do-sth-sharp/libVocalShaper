#include "PhonemeDAO.h"

namespace vocalshaper {
	uint32_t PhonemeDAO::getDeviation(const Phoneme* ptr)
	{
		if (!ptr) {
			return 0;
		}
		return ptr->deviation;
	}

	void PhonemeDAO::setDeviation(Phoneme* ptr, uint32_t deviation)
	{
		if (!ptr) {
			return;
		}
		ptr->saved = false;
		ptr->deviation = deviation;
	}

	juce::String PhonemeDAO::getName(const Phoneme* ptr)
	{
		if (!ptr) {
			return juce::String();
		}
		return ptr->name;
	}

	void PhonemeDAO::setName(Phoneme* ptr, juce::String name)
	{
		if (!ptr) {
			return;
		}
		ptr->saved = false;
		ptr->name = name;
	}

	bool PhonemeDAO::getIsPre(const Phoneme* ptr)
	{
		if (!ptr) {
			return false;
		}
		return ptr->isPre;
	}

	void PhonemeDAO::setIsPre(Phoneme* ptr, bool isPre)
	{
		if (!ptr) {
			return;
		}
		ptr->saved = false;
		ptr->isPre = isPre;
	}

	int PhonemeDAO::timePointSize(const Phoneme* ptr)
	{
		if (!ptr) {
			return -1;
		}
		return ptr->timeMap.size();
	}

	Point* PhonemeDAO::getTimePoint(const Phoneme* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		return ptr->timeMap[index];
	}

	Point* PhonemeDAO::insertTimePoint(Phoneme* ptr, int index, Point* point)
	{
		if (!ptr || !point) {
			return nullptr;
		}
		ptr->saved = false;
		return ptr->timeMap.insert(index, point);
	}

	Point* PhonemeDAO::releaseTimePoint(Phoneme* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		ptr->saved = false;
		return ptr->timeMap.removeAndReturn(index);
	}

	bool PhonemeDAO::isSaved(const Phoneme* ptr)
	{
		return true;
	}

	void PhonemeDAO::save(Phoneme* ptr)
	{

	}

	Phoneme* PhonemeDAO::create()
	{
		return new Phoneme;
	}

	void PhonemeDAO::destory(Phoneme* ptr)
	{
		delete ptr;
	}
}