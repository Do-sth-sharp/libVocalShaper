#include "InstrParamEvent.h"
#include "../daos/ParamDAO.h"

namespace vocalshaper {
	void InstrParamEvent::setTarget(InstrParamEvent::Target target)
	{
		this->target = target;
	}

	const InstrParamEvent::Target InstrParamEvent::getTarget() const
	{
		return this->target;
	}
}