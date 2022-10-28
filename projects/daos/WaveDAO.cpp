#include "WaveDAO.h"

namespace vocalshaper {
	juce::String WaveDAO::getSource(const Wave* ptr)
	{
		if (!ptr) {
			return juce::String();
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->source;
	}

	void WaveDAO::setSource(Wave* ptr, juce::String source)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->source == source) {
			return;
		}
		ptr->saved = false;
		ptr->source = source;
	}

	double WaveDAO::getDeviation(const Wave* ptr)
	{
		if (!ptr) {
			return 0;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->deviation;
	}

	void WaveDAO::setDeviation(Wave* ptr, double deviation)
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

	double WaveDAO::getSt(const Wave* ptr)
	{
		if (!ptr) {
			return 0;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->st;
	}

	void WaveDAO::setSt(Wave* ptr, double time)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->st == time) {
			return;
		}
		ptr->saved = false;
		ptr->st = time;
	}

	double WaveDAO::getLength(const Wave* ptr)
	{
		if (!ptr) {
			return 0;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->length;
	}

	void WaveDAO::setLength(Wave* ptr, double length)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->length == length) {
			return;
		}
		ptr->saved = false;
		ptr->length = length;
	}

	bool WaveDAO::isSaved(const Wave* ptr)
	{
		if (!ptr) {
			return true;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->saved;
	}

	void WaveDAO::save(Wave* ptr)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = true;
	}
}