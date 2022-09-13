#include "DPointEvent.h"
#include "../daos/DPointDAO.h"

namespace vocalshaper {
	DPointEvent::~DPointEvent()
	{
		if (this->ptr) {
			DPointDAO::destory(dynamic_cast<DPoint*>(this->ptr.release()));
		}
	}

	void DPointEvent::setTarget(DPointEvent::Target target)
	{
		this->target = target;
	}

	const DPointEvent::Target DPointEvent::getTarget() const
	{
		return this->target;
	}
}