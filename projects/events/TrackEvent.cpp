#include "TrackEvent.h"
#include "../daos/TrackDAO.h"

namespace vocalshaper {
	TrackEvent::~TrackEvent()
	{
		if (this->ptr1) {
			TrackDAO::destory(this->ptr1.release());
		}
		if (this->ptr2) {
			TrackDAO::destory(this->ptr2.release());
		}
	}

	void TrackEvent::setPtr(Track* ptr)
	{
		if (this->ptr1) {
			TrackDAO::destory(this->ptr1.release());
		}
		this->ptr1.reset(ptr);
	}

	Track* TrackEvent::getPtr() const
	{
		return this->ptr1.get();
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