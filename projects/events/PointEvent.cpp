#include "PointEvent.h"
#include "../daos/PointDAO.h"

namespace vocalshaper {
	PointEvent::~PointEvent()
	{
		if (this->ptr) {
			PointDAO::destory(dynamic_cast<Point*>(this->ptr.release()));
		}
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