#include "InstrParamEvent.h"
#include "../daos/ParamDAO.h"

namespace vocalshaper {
	InstrParamEvent::~InstrParamEvent()
	{
		if (this->ptr1) {
			ParamDAO::destory(this->ptr1.release());
		}
		if (this->ptr2) {
			ParamDAO::destory(this->ptr2.release());
		}
	}

	void InstrParamEvent::setPtr(Param* ptr)
	{
		if (this->ptr1) {
			ParamDAO::destory(this->ptr1.release());
		}
		this->ptr1.reset(ptr);
	}

	Param* InstrParamEvent::getPtr() const
	{
		return this->ptr1.get();
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