#include "CurveEvent.h"
#include "../daos/CurveDAO.h"

namespace vocalshaper {
	void CurveEvent::setTarget(CurveEvent::Target target)
	{
		this->target = target;
	}

	const CurveEvent::Target CurveEvent::getTarget() const
	{
		return this->target;
	}
}