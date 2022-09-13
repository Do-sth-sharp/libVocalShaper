#include "CurveEvent.h"
#include "../daos/CurveDAO.h"

namespace vocalshaper {
	CurveEvent::~CurveEvent()
	{
		if (this->ptr) {
			CurveDAO::destory(dynamic_cast<Curve*>(this->ptr.release()));
		}
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