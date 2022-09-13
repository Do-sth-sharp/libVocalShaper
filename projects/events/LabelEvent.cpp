#include "LabelEvent.h"
#include "../daos/LabelDAO.h"

namespace vocalshaper {
	LabelEvent::~LabelEvent()
	{
		if (this->ptr) {
			LabelDAO::destory(dynamic_cast<Label*>(this->ptr.release()));
		}
	}

	void LabelEvent::setTarget(LabelEvent::Target target)
	{
		this->target = target;
	}

	const LabelEvent::Target LabelEvent::getTarget() const
	{
		return this->target;
	}
}