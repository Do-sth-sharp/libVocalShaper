#include "InstrEvent.h"
#include "../daos/InstrDAO.h"

namespace vocalshaper {
	InstrEvent::~InstrEvent()
	{
		if (this->ptr1) {
			InstrDAO::destory(this->ptr1.release());
		}
		if (this->ptr2) {
			InstrDAO::destory(this->ptr2.release());
		}
	}

	void InstrEvent::setPtr(Instr* ptr)
	{
		if (this->ptr1) {
			InstrDAO::destory(this->ptr1.release());
		}
		this->ptr1.reset(ptr);
	}

	Instr* InstrEvent::getPtr() const
	{
		return this->ptr1.get();
	}

	void InstrEvent::setTarget(InstrEvent::Target target)
	{
		this->target = target;
	}

	const InstrEvent::Target InstrEvent::getTarget() const
	{
		return this->target;
	}
}