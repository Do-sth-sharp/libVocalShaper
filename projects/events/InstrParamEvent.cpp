#include "InstrParamEvent.h"
#include "../daos/ParamDAO.h"

namespace vocalshaper {
	InstrParamEvent::~InstrParamEvent()
	{
		if (this->ptr) {
			ParamDAO::destory(dynamic_cast<Param*>(this->ptr.release()));
		}
	}

	void InstrParamEvent::setTarget(InstrParamEvent::Target target)
	{
		this->target = target;
	}

	const InstrParamEvent::Target InstrParamEvent::getTarget() const
	{
		return this->target;
	}
}