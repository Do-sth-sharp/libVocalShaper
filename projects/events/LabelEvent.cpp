#include "LabelEvent.h"
#include "../daos/LabelDAO.h"

namespace vocalshaper {
	void LabelEvent::setTarget(LabelEvent::Target target)
	{
		this->target = target;
	}

	const LabelEvent::Target LabelEvent::getTarget() const
	{
		return this->target;
	}
}