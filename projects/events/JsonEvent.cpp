#include "JsonEvent.h"
#include "../daos/JsonDAO.h"

namespace vocalshaper {
	JsonEvent::~JsonEvent()
	{
		if (this->ptr1) {
			JsonDAO::destory(this->ptr1.release());
		}
		if (this->ptr2) {
			JsonDAO::destory(this->ptr2.release());
		}
	}

	void JsonEvent::setPtr(Json* ptr)
	{
		if (this->ptr1) {
			JsonDAO::destory(this->ptr1.release());
		}
		this->ptr1.reset(ptr);
	}

	Json* JsonEvent::getPtr() const
	{
		return this->ptr1.get();
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