#include "NoteEvent.h"
#include "../daos/NoteDAO.h"

namespace vocalshaper {
	NoteEvent::~NoteEvent()
	{
		if (this->ptr) {
			NoteDAO::destory(dynamic_cast<Note*>(this->ptr.release()));
		}
	}

	void NoteEvent::setTarget(NoteEvent::Target target)
	{
		this->target = target;
	}

	const NoteEvent::Target NoteEvent::getTarget() const
	{
		return this->target;
	}
}