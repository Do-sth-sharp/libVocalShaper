#include "ProjectEvent.h"
#include "../daos/ProjectDAO.h"

namespace vocalshaper {
	ProjectEvent::~ProjectEvent()
	{
		if (this->ptr1) {
			ProjectDAO::destory(this->ptr1.release());
		}
		if (this->ptr2) {
			ProjectDAO::destory(this->ptr2.release());
		}
	}
}