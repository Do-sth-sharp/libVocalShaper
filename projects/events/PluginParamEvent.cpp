#include "PluginParamEvent.h"
#include "../daos/ParamDAO.h"

namespace vocalshaper {
	PluginParamEvent::~PluginParamEvent()
	{
		if (this->ptr) {
			ParamDAO::destory(dynamic_cast<Param*>(this->ptr.release()));
		}
	}

	void PluginParamEvent::setTarget(PluginParamEvent::Target target)
	{
		this->target = target;
	}

	const PluginParamEvent::Target PluginParamEvent::getTarget() const
	{
		return this->target;
	}
}