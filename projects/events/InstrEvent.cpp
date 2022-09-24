#include "InstrEvent.h"
#include "../daos/InstrDAO.h"

namespace vocalshaper {
	void InstrEvent::setTarget(InstrEvent::Target target)
	{
		this->target = target;
	}

	const InstrEvent::Target InstrEvent::getTarget() const
	{
		return this->target;
	}
}