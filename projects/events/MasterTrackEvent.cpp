#include "MasterTrackEvent.h"
#include "../daos/TrackDAO.h"

namespace vocalshaper {
	void MasterTrackEvent::setTarget(MasterTrackEvent::Target target)
	{
		this->target = target;
	}

	const MasterTrackEvent::Target MasterTrackEvent::getTarget() const
	{
		return this->target;
	}
}