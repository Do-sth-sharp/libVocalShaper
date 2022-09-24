#include "TrackParamEvent.h"
#include "../daos/ParamDAO.h"

namespace vocalshaper {
	void TrackParamEvent::setTarget(TrackParamEvent::Target target)
	{
		this->target = target;
	}

	const TrackParamEvent::Target TrackParamEvent::getTarget() const
	{
		return this->target;
	}
}