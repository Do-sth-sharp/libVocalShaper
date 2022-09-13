#include "NoteParamEvent.h"
#include "../daos/ParamDAO.h"

namespace vocalshaper {
	NoteParamEvent::~NoteParamEvent()
	{
		if (this->ptr) {
			ParamDAO::destory(dynamic_cast<Param*>(this->ptr.release()));
		}
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