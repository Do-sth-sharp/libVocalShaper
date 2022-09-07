#include "PointEvent.h"
#include "../daos/PointDAO.h"

namespace vocalshaper {
	PointEvent::~PointEvent()
	{
		if (this->ptr1) {
			PointDAO::destory(this->ptr1.release());
		}
		if (this->ptr2) {
			PointDAO::destory(this->ptr2.release());
		}
	}
}