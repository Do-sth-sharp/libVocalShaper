#include "JsonEvent.h"
#include "../daos/JsonDAO.h"

namespace vocalshaper {
	void JsonEvent::setTarget(JsonEvent::Target target)
	{
		this->target = target;
	}

	const JsonEvent::Target JsonEvent::getTarget() const
	{
		return this->target;
	}
}