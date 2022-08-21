#include "SerializableProjectStructure.h"

namespace vocalshaper {
	SerializableProjectStructure::SerializableProjectStructure(Type type)
		:type(type) {};

	SerializableProjectStructure::Type SerializableProjectStructure::getType() const
	{
		return this->type;
	}
}