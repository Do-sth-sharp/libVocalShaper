#include "LabelEvent.h"
#include "../daos/LabelDAO.h"

namespace vocalshaper {
	LabelEvent::~LabelEvent()
	{
		if (this->ptr1) {
			LabelDAO::destory(this->ptr1.release());
		}
		if (this->ptr2) {
			LabelDAO::destory(this->ptr2.release());
		}
	}

	void LabelEvent::setPtr(Label* ptr)
	{
		if (this->ptr1) {
			LabelDAO::destory(this->ptr1.release());
		}
		this->ptr1.reset(ptr);
	}

	Label* LabelEvent::getPtr() const
	{
		return this->ptr1.get();
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