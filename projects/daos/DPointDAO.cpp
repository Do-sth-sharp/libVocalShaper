#include "DPointDAO.h"

namespace vocalshaper {
	ProjectTime DPointDAO::getTime(const DPoint* ptr)
	{
		if (!ptr) {
			return make_time(0, 0);
		}
		return ptr->x;
	}

	void DPointDAO::setTime(DPoint* ptr, ProjectTime time)
	{
		if (!ptr) {
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
		return ptr->y;
	}

	void DPointDAO::setY(DPoint* ptr, double y)
	{
		if (!ptr) {
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
		return ptr->dl;
	}

	void DPointDAO::setDl(DPoint* ptr, double dl)
	{
		if (!ptr) {
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
		return ptr->dr;
	}

	void DPointDAO::setDr(DPoint* ptr, double dr)
	{
		if (!ptr) {
			return;
		}
		ptr->saved = false;
		ptr->dr = dr;
	}

	bool DPointDAO::isSaved(const DPoint* ptr)
	{
		return true;
	}

	void DPointDAO::save(DPoint* ptr)
	{

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