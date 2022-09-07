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
}