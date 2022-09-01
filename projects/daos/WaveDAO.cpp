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

	uint64_t WaveDAO::getDeviation(const Wave* ptr)
	{
		if (!ptr) {
			return 0;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->deviation;
	}

	void WaveDAO::setDeviation(Wave* ptr, uint64_t deviation)
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

	ProjectTime WaveDAO::getSt(const Wave* ptr)
	{
		if (!ptr) {
			return make_time(0, 0);
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->st;
	}

	void WaveDAO::setSt(Wave* ptr, ProjectTime time)
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

	uint32_t WaveDAO::getLength(const Wave* ptr)
	{
		if (!ptr) {
			return 0;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->length;
	}

	void WaveDAO::setLength(Wave* ptr, uint32_t length)
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

	Wave* WaveDAO::create()
	{
		return new Wave;
	}

	void WaveDAO::destory(Wave* ptr)
	{
		delete ptr;
	}
}