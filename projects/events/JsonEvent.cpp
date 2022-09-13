#include "JsonEvent.h"
#include "../daos/JsonDAO.h"

namespace vocalshaper {
	JsonEvent::~JsonEvent()
	{
		if (this->ptr) {
			JsonDAO::destory(dynamic_cast<Json*>(this->ptr.release()));
		}
	}

	void JsonEvent::setTarget(JsonEvent::Target target)
	{
		this->target = target;
	}

	const JsonEvent::Target JsonEvent::getTarget() const
	{
		return this->target;
	}
}