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

	void ProjectEvent::setPtr(Project* ptr)
	{
		if (this->ptr1) {
			ProjectDAO::destory(this->ptr1.release());
		}
		this->ptr1.reset(ptr);
	}

	Project* ProjectEvent::getPtr() const
	{
		return this->ptr1.get();
	}

	void ProjectEvent::setTarget(ProjectEvent::Target target)
	{
		this->target = target;
	}

	const ProjectEvent::Target ProjectEvent::getTarget() const
	{
		return this->target;
	}
}