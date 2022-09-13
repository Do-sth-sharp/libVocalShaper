#include "ScriptEvent.h"
#include "../daos/ScriptDAO.h"

namespace vocalshaper {
	ScriptEvent::~ScriptEvent()
	{
		if (this->ptr) {
			ScriptDAO::destory(dynamic_cast<Script*>(this->ptr.release()));
		}
	}

	void ScriptEvent::setTarget(ScriptEvent::Target target)
	{
		this->target = target;
	}

	const ScriptEvent::Target ScriptEvent::getTarget() const
	{
		return this->target;
	}
}