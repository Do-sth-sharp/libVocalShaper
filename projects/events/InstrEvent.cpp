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
}