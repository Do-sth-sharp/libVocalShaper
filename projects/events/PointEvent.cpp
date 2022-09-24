#include "PointEvent.h"
#include "../daos/PointDAO.h"

namespace vocalshaper {
	void PointEvent::setTarget(PointEvent::Target target)
	{
		this->target = target;
	}

	const PointEvent::Target PointEvent::getTarget() const
	{
		return this->target;
	}
}