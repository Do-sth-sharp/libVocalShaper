#include "ProjectEvent.h"
#include "../daos/ProjectDAO.h"

namespace vocalshaper {
	void ProjectEvent::setTarget(ProjectEvent::Target target)
	{
		this->target = target;
	}

	const ProjectEvent::Target ProjectEvent::getTarget() const
	{
		return this->target;
	}
}