#include "PluginParamEvent.h"
#include "../daos/ParamDAO.h"

namespace vocalshaper {
	void PluginParamEvent::setTarget(PluginParamEvent::Target target)
	{
		this->target = target;
	}

	const PluginParamEvent::Target PluginParamEvent::getTarget() const
	{
		return this->target;
	}
}