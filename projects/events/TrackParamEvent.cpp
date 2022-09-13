#include "TrackParamEvent.h"
#include "../daos/ParamDAO.h"

namespace vocalshaper {
	TrackParamEvent::~TrackParamEvent()
	{
		if (this->ptr) {
			ParamDAO::destory(dynamic_cast<Param*>(this->ptr.release()));
		}
	}

	void TrackParamEvent::setTarget(TrackParamEvent::Target target)
	{
		this->target = target;
	}

	const TrackParamEvent::Target TrackParamEvent::getTarget() const
	{
		return this->target;
	}
}