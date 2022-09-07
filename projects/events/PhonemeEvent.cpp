#include "PhonemeEvent.h"
#include "../daos/PhonemeDAO.h"

namespace vocalshaper {
	PhonemeEvent::~PhonemeEvent()
	{
		if (this->ptr1) {
			PhonemeDAO::destory(this->ptr1.release());
		}
		if (this->ptr2) {
			PhonemeDAO::destory(this->ptr2.release());
		}
	}
}