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
}