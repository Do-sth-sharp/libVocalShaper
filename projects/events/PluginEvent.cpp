#include "PluginEvent.h"
#include "../daos/PluginDAO.h"

namespace vocalshaper {
	void PluginEvent::setTarget(PluginEvent::Target target)
	{
		this->target = target;
	}

	const PluginEvent::Target PluginEvent::getTarget() const
	{
		return this->target;
	}
}