#include "PointEvent.h"
#include "../daos/PointDAO.h"

namespace vocalshaper {
	PointEvent::~PointEvent()
	{
		if (this->ptr1) {
			PointDAO::destory(this->ptr1.release());
		}
		if (this->ptr2) {
			PointDAO::destory(this->ptr2.release());
		}
	}

	void PointEvent::setPtr(Point* ptr)
	{
		if (this->ptr1) {
			PointDAO::destory(this->ptr1.release());
		}
		this->ptr1.reset(ptr);
	}

	Point* PointEvent::getPtr() const
	{
		return this->ptr1.get();
	}

	void PointEvent::setTarget(PointEvent::Target target)
	{
		this->target = target;
	}

	const PointEvent::Target PointEvent::getTarget() const
	{
		return this->target;
	}
}