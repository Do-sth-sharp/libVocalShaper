#include "InstrEvent.h"
#include "../daos/InstrDAO.h"

namespace vocalshaper {
	InstrEvent::~InstrEvent()
	{
		if (this->ptr) {
			InstrDAO::destory(dynamic_cast<Instr*>(this->ptr.release()));
		}
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