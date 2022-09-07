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
}