#include "CurveDAO.h"

namespace vocalshaper {
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

	Curve* CurveDAO::create()
	{
		return new Curve;
	}

	void CurveDAO::destory(Curve* ptr)
	{
		delete ptr;
	}
}