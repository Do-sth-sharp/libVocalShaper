#include "PhonemeDAO.h"

namespace vocalshaper {
	uint32_t PhonemeDAO::getDeviation(const Phoneme* ptr)
	{
		if (!ptr) {
			return 0;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->deviation;
	}

	void PhonemeDAO::setDeviation(Phoneme* ptr, uint32_t deviation)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->deviation == deviation) {
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
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->name;
	}

	void PhonemeDAO::setName(Phoneme* ptr, juce::String name)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->name == name) {
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
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->isPre;
	}

	void PhonemeDAO::setIsPre(Phoneme* ptr, bool isPre)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->isPre == isPre) {
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
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->timeMap.size();
	}

	Point* PhonemeDAO::getTimePoint(const Phoneme* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->timeMap[index];
	}

	Point* PhonemeDAO::insertTimePoint(Phoneme* ptr, int index, Point* point)
	{
		if (!ptr || !point) {
			return nullptr;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = false;
		return ptr->timeMap.insert(index, point);
	}

	Point* PhonemeDAO::releaseTimePoint(Phoneme* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = false;
		return ptr->timeMap.removeAndReturn(index);
	}

	bool PhonemeDAO::isSaved(const Phoneme* ptr)
	{
		if (!ptr) {
			return true;
		}
		juce::ScopedReadLock locker(ptr->lock);
		if (!ptr->saved) {
			return false;
		}
		for (auto i : ptr->timeMap) {
			if (!PointDAO::isSaved(i)) {
				return false;
			}
		}
		return true;
	}

	void PhonemeDAO::save(Phoneme* ptr)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = true;
		for (auto i : ptr->timeMap) {
			PointDAO::save(i);
		}
	}
}