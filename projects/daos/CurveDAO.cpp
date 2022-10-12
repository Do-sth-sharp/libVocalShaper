#include "CurveDAO.h"

namespace vocalshaper {
	juce::String CurveDAO::getId(const Curve* ptr)
	{
		if (!ptr) {
			return juce::String();
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->id;
	}

	void CurveDAO::setId(Curve* ptr, juce::String id)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->id == id) {
			return;
		}
		ptr->saved = false;
		ptr->id = id;
	}

	int CurveDAO::pointSize(const Curve* ptr)
	{
		if (!ptr) {
			return -1;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->points.size();
	}

	DPoint* CurveDAO::getPoint(const Curve* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->points[index];
	}

	DPoint* CurveDAO::insertPoint(Curve* ptr, int index, DPoint* point)
	{
		if (!ptr || !point) {
			return nullptr;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->points.size() >= INT_MAX - 1) {
			return nullptr;
		}
		ptr->saved = false;
		return ptr->points.insert(index, point);
	}

	DPoint* CurveDAO::releasePoint(Curve* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = false;
		return ptr->points.removeAndReturn(index);
	}

	bool CurveDAO::isSaved(const Curve* ptr)
	{
		if (!ptr) {
			return true;
		}
		juce::ScopedReadLock locker(ptr->lock);
		if (!ptr->saved) {
			return false;
		}
		for (auto i : ptr->points) {
			if (!DPointDAO::isSaved(i)) {
				return false;
			}
		}
		return true;
	}

	void CurveDAO::save(Curve* ptr)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = true;
		for (auto i : ptr->points) {
			DPointDAO::save(i);
		}
	}
}