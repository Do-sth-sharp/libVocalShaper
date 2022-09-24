#include "NoteParamEvent.h"
#include "../daos/ParamDAO.h"

namespace vocalshaper {
	void NoteParamEvent::setTarget(NoteParamEvent::Target target)
	{
		this->target = target;
	}

	const NoteParamEvent::Target NoteParamEvent::getTarget() const
	{
		return this->target;
	}
}