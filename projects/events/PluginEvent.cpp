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

	void PluginEvent::setPtr(Plugin* ptr)
	{
		if (this->ptr1) {
			PluginDAO::destory(this->ptr1.release());
		}
		this->ptr1.reset(ptr);
	}

	Plugin* PluginEvent::getPtr() const
	{
		return this->ptr1.get();
	}

	void PluginEvent::setTarget(PluginEvent::Target target)
	{
		this->target = target;
	}

	const PluginEvent::Target PluginEvent::getTarget() const
	{
		return this->target;
	}
}