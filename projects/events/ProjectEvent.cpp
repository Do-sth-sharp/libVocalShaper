#include "ProjectEvent.h"
#include "../daos/ProjectDAO.h"

namespace vocalshaper {
	ProjectEvent::~ProjectEvent()
	{
		if (this->ptr) {
			ProjectDAO::destory(dynamic_cast<Project*>(this->ptr.release()));
		}
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