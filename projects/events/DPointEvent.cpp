#include "DPointEvent.h"
#include "../daos/DPointDAO.h"

namespace vocalshaper {
	DPointEvent::~DPointEvent()
	{
		if (this->ptr1) {
			DPointDAO::destory(this->ptr1.release());
		}
		if (this->ptr2) {
			DPointDAO::destory(this->ptr2.release());
		}
	}

	void DPointEvent::setPtr(DPoint* ptr)
	{
		if (this->ptr1) {
			DPointDAO::destory(this->ptr1.release());
		}
		this->ptr1.reset(ptr);
	}

	DPoint* DPointEvent::getPtr() const
	{
		return this->ptr1.get();
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