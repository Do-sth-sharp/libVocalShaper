#include "DPointDAO.h"

namespace vocalshaper {
	ProjectTime DPointDAO::getTime(const DPoint* ptr)
	{
		if (!ptr) {
			return make_time(0, 0);
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->x;
	}

	void DPointDAO::setTime(DPoint* ptr, ProjectTime time)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->x == time) {
			return;
		}
		ptr->saved = false;
		ptr->x = time;
	}

	double DPointDAO::getY(const DPoint* ptr)
	{
		if (!ptr) {
			return 0;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->y;
	}

	void DPointDAO::setY(DPoint* ptr, double y)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->y == y) {
			return;
		}
		ptr->saved = false;
		ptr->y = y;
	}

	double DPointDAO::getDl(const DPoint* ptr)
	{
		if (!ptr) {
			return 0;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->dl;
	}

	void DPointDAO::setDl(DPoint* ptr, double dl)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->dl == dl) {
			return;
		}
		ptr->saved = false;
		ptr->dl = dl;
	}

	double DPointDAO::getDr(const DPoint* ptr)
	{
		if (!ptr) {
			return 0;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->dr;
	}

	void DPointDAO::setDr(DPoint* ptr, double dr)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->dr == dr) {
			return;
		}
		ptr->saved = false;
		ptr->dr = dr;
	}

	bool DPointDAO::isSaved(const DPoint* ptr)
	{
		if (!ptr) {
			return true;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->saved;
	}

	void DPointDAO::save(DPoint* ptr)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = true;
	}

	DPoint* DPointDAO::create()
	{
		return new DPoint;
	}

	void DPointDAO::destory(DPoint* ptr)
	{
		delete ptr;
	}
}