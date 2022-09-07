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
}