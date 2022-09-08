#include "NoteEvent.h"
#include "../daos/NoteDAO.h"

namespace vocalshaper {
	NoteEvent::~NoteEvent()
	{
		if (this->ptr1) {
			NoteDAO::destory(this->ptr1.release());
		}
		if (this->ptr2) {
			NoteDAO::destory(this->ptr2.release());
		}
	}

	void NoteEvent::setPtr(Note* ptr)
	{
		if (this->ptr1) {
			NoteDAO::destory(this->ptr1.release());
		}
		this->ptr1.reset(ptr);
	}

	Note* NoteEvent::getPtr() const
	{
		return this->ptr1.get();
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