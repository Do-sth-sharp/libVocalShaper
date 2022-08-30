#include "CurveDAO.h"

namespace vocalshaper {
	int CurveDAO::pointSize(const Curve* ptr)
	{
		if (!ptr) {
			return -1;
		}
		return ptr->points.size();
	}

	DPoint* CurveDAO::getPoint(const Curve* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		return ptr->points[index];
	}

	DPoint* CurveDAO::insertPoint(Curve* ptr, int index, DPoint* point)
	{
		if (!ptr || !point) {
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
		ptr->saved = false;
		return ptr->points.removeAndReturn(index);
	}

	bool CurveDAO::isSaved(const Curve* ptr)
	{
		return true;
	}

	void CurveDAO::save(Curve* ptr)
	{

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