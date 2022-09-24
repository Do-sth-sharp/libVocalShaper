#include "TrackEvent.h"
#include "../daos/TrackDAO.h"

namespace vocalshaper {
	void TrackEvent::setTarget(TrackEvent::Target target)
	{
		this->target = target;
	}

	const TrackEvent::Target TrackEvent::getTarget() const
	{
		return this->target;
	}
}