#include "TrackEvent.h"
#include "../daos/TrackDAO.h"

namespace vocalshaper {
	TrackEvent::~TrackEvent()
	{
		if (this->ptr) {
			TrackDAO::destory(dynamic_cast<Track*>(this->ptr.release()));
		}
	}

	void TrackEvent::setTarget(TrackEvent::Target target)
	{
		this->target = target;
	}

	const TrackEvent::Target TrackEvent::getTarget() const
	{
		return this->target;
	}
}