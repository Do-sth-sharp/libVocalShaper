#include "MasterTrackEvent.h"
#include "../daos/TrackDAO.h"

namespace vocalshaper {
	MasterTrackEvent::~MasterTrackEvent()
	{
		if (this->ptr1) {
			TrackDAO::destory(this->ptr1.release());
		}
		if (this->ptr2) {
			TrackDAO::destory(this->ptr2.release());
		}
	}

	void MasterTrackEvent::setPtr(Track* ptr)
	{
		if (this->ptr1) {
			TrackDAO::destory(this->ptr1.release());
		}
		this->ptr1.reset(ptr);
	}

	Track* MasterTrackEvent::getPtr() const
	{
		return this->ptr1.get();
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