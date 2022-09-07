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
}