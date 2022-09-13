#include "PluginEvent.h"
#include "../daos/PluginDAO.h"

namespace vocalshaper {
	PluginEvent::~PluginEvent()
	{
		if (this->ptr) {
			PluginDAO::destory(dynamic_cast<Plugin*>(this->ptr.release()));
		}
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