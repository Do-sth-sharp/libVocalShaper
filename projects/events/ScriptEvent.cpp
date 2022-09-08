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

	void ScriptEvent::setPtr(Script* ptr)
	{
		if (this->ptr1) {
			ScriptDAO::destory(this->ptr1.release());
		}
		this->ptr1.reset(ptr);
	}

	Script* ScriptEvent::getPtr() const
	{
		return this->ptr1.get();
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