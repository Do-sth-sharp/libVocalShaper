#include "MasterTrackEvent.h"
#include "../daos/TrackDAO.h"

namespace vocalshaper {
	MasterTrackEvent::~MasterTrackEvent()
	{
		if (this->ptr) {
			TrackDAO::destory(dynamic_cast<Track*>(this->ptr.release()));
		}
	}

	void MasterTrackEvent::setTarget(MasterTrackEvent::Target target)
	{
		this->target = target;
	}

	const MasterTrackEvent::Target MasterTrackEvent::getTarget() const
	{
		return this->target;
	}
}