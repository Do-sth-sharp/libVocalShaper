#include "PluginEvent.h"
#include "../daos/PluginDAO.h"

namespace vocalshaper {
	PluginEvent::~PluginEvent()
	{
		if (this->ptr1) {
			PluginDAO::destory(this->ptr1.release());
		}
		if (this->ptr2) {
			PluginDAO::destory(this->ptr2.release());
		}
	}
}