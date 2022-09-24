#include "PointDAO.h"

namespace vocalshaper {
	double PointDAO::getX(const Point* ptr)
	{
		if (!ptr) {
			return 0;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->x;
	}

	double PointDAO::getY(const Point* ptr)
	{
		if (!ptr) {
			return 0;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->y;
	}

	void PointDAO::setX(Point* ptr, double x)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->x == x) {
			return;
		}
		ptr->saved = false;
		ptr->x = x;
	}

	void PointDAO::setY(Point* ptr, double y)
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

	bool PointDAO::isSaved(const Point* ptr)
	{
		if (!ptr) {
			return true;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->saved;
	}

	void PointDAO::save(Point* ptr)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = true;
	}
}