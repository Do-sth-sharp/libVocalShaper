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
}