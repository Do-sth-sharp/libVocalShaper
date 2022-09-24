#include "DPointEvent.h"
#include "../daos/DPointDAO.h"

namespace vocalshaper {
	void DPointEvent::setTarget(DPointEvent::Target target)
	{
		this->target = target;
	}

	const DPointEvent::Target DPointEvent::getTarget() const
	{
		return this->target;
	}
}