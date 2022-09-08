#include "NoteParamEvent.h"
#include "../daos/ParamDAO.h"

namespace vocalshaper {
	NoteParamEvent::~NoteParamEvent()
	{
		if (this->ptr1) {
			ParamDAO::destory(this->ptr1.release());
		}
		if (this->ptr2) {
			ParamDAO::destory(this->ptr2.release());
		}
	}

	void NoteParamEvent::setPtr(Param* ptr)
	{
		if (this->ptr1) {
			ParamDAO::destory(this->ptr1.release());
		}
		this->ptr1.reset(ptr);
	}

	Param* NoteParamEvent::getPtr() const
	{
		return this->ptr1.get();
	}

	void NoteParamEvent::setTarget(NoteParamEvent::Target target)
	{
		this->target = target;
	}

	const NoteParamEvent::Target NoteParamEvent::getTarget() const
	{
		return this->target;
	}
}