#include "PhonemeEvent.h"
#include "../daos/PhonemeDAO.h"

namespace vocalshaper {
	void PhonemeEvent::setTarget(PhonemeEvent::Target target)
	{
		this->target = target;
	}

	const PhonemeEvent::Target PhonemeEvent::getTarget() const
	{
		return this->target;
	}
}