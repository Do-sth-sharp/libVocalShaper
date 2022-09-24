#include "ScriptEvent.h"
#include "../daos/ScriptDAO.h"

namespace vocalshaper {
	void ScriptEvent::setTarget(ScriptEvent::Target target)
	{
		this->target = target;
	}

	const ScriptEvent::Target ScriptEvent::getTarget() const
	{
		return this->target;
	}
}