#include "PointDAO.h"

namespace vocalshaper {
	double PointDAO::getX(const Point* ptr)
	{
		if (!ptr) {
			return 0;
		}
		return ptr->x;
	}

	double PointDAO::getY(const Point* ptr)
	{
		if (!ptr) {
			return 0;
		}
		return ptr->y;
	}

	void PointDAO::setX(Point* ptr, double x)
	{
		if (!ptr) {
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
		ptr->saved = false;
		ptr->y = y;
	}

	bool PointDAO::isSaved(const Point* ptr)
	{
		return true;
	}

	void PointDAO::save(Point* ptr)
	{

	}

	Point* PointDAO::create()
	{
		return new Point;
	}

	void PointDAO::destory(Point* ptr)
	{
		delete ptr;
	}
}