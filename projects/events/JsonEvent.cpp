#include "JsonEvent.h"
#include "../daos/JsonDAO.h"

namespace vocalshaper {
	JsonEvent::~JsonEvent()
	{
		if (this->ptr1) {
			JsonDAO::destory(this->ptr1.release());
		}
		if (this->ptr2) {
			JsonDAO::destory(this->ptr2.release());
		}
	}
}