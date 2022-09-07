#include "ScriptEvent.h"
#include "../daos/ScriptDAO.h"

namespace vocalshaper {
	ScriptEvent::~ScriptEvent()
	{
		if (this->ptr1) {
			ScriptDAO::destory(this->ptr1.release());
		}
		if (this->ptr2) {
			ScriptDAO::destory(this->ptr2.release());
		}
	}
}