#include "CurveEvent.h"
#include "../daos/CurveDAO.h"

namespace vocalshaper {
	CurveEvent::~CurveEvent()
	{
		if (this->ptr1) {
			CurveDAO::destory(this->ptr1.release());
		}
		if (this->ptr2) {
			CurveDAO::destory(this->ptr2.release());
		}
	}

	void CurveEvent::setPtr(Curve* ptr)
	{
		if (this->ptr1) {
			CurveDAO::destory(this->ptr1.release());
		}
		this->ptr1.reset(ptr);
	}

	Curve* CurveEvent::getPtr() const
	{
		return this->ptr1.get();
	}

	void CurveEvent::setTarget(CurveEvent::Target target)
	{
		this->target = target;
	}

	const CurveEvent::Target CurveEvent::getTarget() const
	{
		return this->target;
	}
}