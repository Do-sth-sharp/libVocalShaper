#include "NoteEvent.h"
#include "../daos/NoteDAO.h"

namespace vocalshaper {
	void NoteEvent::setTarget(NoteEvent::Target target)
	{
		this->target = target;
	}

	const NoteEvent::Target NoteEvent::getTarget() const
	{
		return this->target;
	}
}