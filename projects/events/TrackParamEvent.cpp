#include "TrackParamEvent.h"
#include "../daos/ParamDAO.h"

namespace vocalshaper {
	TrackParamEvent::~TrackParamEvent()
	{
		if (this->ptr1) {
			ParamDAO::destory(this->ptr1.release());
		}
		if (this->ptr2) {
			ParamDAO::destory(this->ptr2.release());
		}
	}

	void TrackParamEvent::setPtr(Param* ptr)
	{
		if (this->ptr1) {
			ParamDAO::destory(this->ptr1.release());
		}
		this->ptr1.reset(ptr);
	}

	Param* TrackParamEvent::getPtr() const
	{
		return this->ptr1.get();
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