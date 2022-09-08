#include "PluginParamEvent.h"
#include "../daos/ParamDAO.h"

namespace vocalshaper {
	PluginParamEvent::~PluginParamEvent()
	{
		if (this->ptr1) {
			ParamDAO::destory(this->ptr1.release());
		}
		if (this->ptr2) {
			ParamDAO::destory(this->ptr2.release());
		}
	}

	void PluginParamEvent::setPtr(Param* ptr)
	{
		if (this->ptr1) {
			ParamDAO::destory(this->ptr1.release());
		}
		this->ptr1.reset(ptr);
	}

	Param* PluginParamEvent::getPtr() const
	{
		return this->ptr1.get();
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