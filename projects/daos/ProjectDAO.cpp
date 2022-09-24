#include "ProjectDAO.h"

namespace vocalshaper {
	uint32_t ProjectDAO::getSampleRate(const Project* ptr)
	{
		if (!ptr) {
			return 0;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->sampleRate;
	}

	void ProjectDAO::setSampleRate(Project* ptr, uint32_t sampleRate)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->sampleRate == sampleRate) {
			return;
		}
		ptr->saved = false;
		ptr->sampleRate = sampleRate;
	}

	uint32_t ProjectDAO::getBitDeepth(const Project* ptr)
	{
		if (!ptr) {
			return 0;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->bitDeepth;
	}

	void ProjectDAO::setBitDeepth(Project* ptr, uint32_t bitDeepth)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->bitDeepth == bitDeepth) {
			return;
		}
		ptr->saved = false;
		ptr->bitDeepth = bitDeepth;
	}

	uint32_t ProjectDAO::getCurveQuantification(const Project* ptr)
	{
		if (!ptr) {
			return 0;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->curveQuantification;
	}

	void ProjectDAO::setCurveQuantification(Project* ptr, uint32_t curveQuantification)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->curveQuantification == curveQuantification) {
			return;
		}
		ptr->saved = false;
		ptr->curveQuantification = curveQuantification;
	}

	Track* ProjectDAO::getMasterTrack(const Project* ptr)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->masterTrack.get();
	}

	int ProjectDAO::trackSize(const Project* ptr)
	{
		if (!ptr) {
			return -1;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->tracks.size();
	}

	Track* ProjectDAO::getTrack(const Project* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->tracks[index];
	}

	Track* ProjectDAO::insertTrack(Project* ptr, int index, Track* track)
	{
		if (!ptr || !track) {
			return nullptr;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = false;
		return ptr->tracks.insert(index, track);
	}

	Track* ProjectDAO::releaseTrack(Project* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = false;
		return ptr->tracks.removeAndReturn(index);
	}

	int ProjectDAO::labelSize(const Project* ptr)
	{
		if (!ptr) {
			return -1;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->labels.size();
	}

	Label* ProjectDAO::getLabel(const Project* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->labels[index];
	}

	Label* ProjectDAO::insertLabel(Project* ptr, int index, Label* label)
	{
		if (!ptr || !label) {
			return nullptr;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = false;
		return ptr->labels.insert(index, label);
	}

	Label* ProjectDAO::releaseLabel(Project* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = false;
		return ptr->labels.removeAndReturn(index);
	}

	int ProjectDAO::scriptSize(const Project* ptr)
	{
		if (!ptr) {
			return -1;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->scripts.size();
	}

	Script* ProjectDAO::getScript(const Project* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->scripts[index];
	}

	Script* ProjectDAO::insertScript(Project* ptr, int index, Script* script)
	{
		if (!ptr || !script) {
			return nullptr;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = false;
		return ptr->scripts.insert(index, script);
	}

	Script* ProjectDAO::releaseScript(Project* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = false;
		return ptr->scripts.removeAndReturn(index);
	}

	int ProjectDAO::additionSize(const Project* ptr)
	{
		if (!ptr) {
			return -1;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->additions.size();
	}

	Json* ProjectDAO::getAddition(const Project* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->additions[index];
	}

	Json* ProjectDAO::insertAddition(Project* ptr, int index, Json* addition)
	{
		if (!ptr || !addition) {
			return nullptr;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = false;
		return ptr->additions.insert(index, addition);
	}

	Json* ProjectDAO::releaseAddition(Project* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = false;
		return ptr->additions.removeAndReturn(index);
	}

	bool ProjectDAO::isSaved(const Project* ptr)
	{
		if (!ptr) {
			return true;
		}
		juce::ScopedReadLock locker(ptr->lock);
		if (!ptr->saved) {
			return false;
		}
		if (!TrackDAO::isSaved(ptr->masterTrack.get())) {
			return false;
		}
		for (auto i : ptr->tracks) {
			if (!TrackDAO::isSaved(i)) {
				return false;
			}
		}
		for (auto i : ptr->labels) {
			if (!LabelDAO::isSaved(i)) {
				return false;
			}
		}
		for (auto i : ptr->scripts) {
			if (!ScriptDAO::isSaved(i)) {
				return false;
			}
		}
		for (auto i : ptr->additions) {
			if (!JsonDAO::isSaved(i)) {
				return false;
			}
		}
		return true;
	}

	void ProjectDAO::save(Project* ptr)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = true;
		TrackDAO::save(ptr->masterTrack.get());
		for (auto i : ptr->tracks) {
			TrackDAO::save(i);
		}
		for (auto i : ptr->labels) {
			LabelDAO::save(i);
		}
		for (auto i : ptr->scripts) {
			ScriptDAO::save(i);
		}
		for (auto i : ptr->additions) {
			JsonDAO::save(i);
		}
	}
}