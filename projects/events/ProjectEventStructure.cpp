#include "ProjectEventStructure.h"

namespace vocalshaper {
	ProjectEventStructure::ProjectEventStructure(Type type, ChangeType cType)
		:type(type), cType(cType) {};

	ProjectEventStructure::Type ProjectEventStructure::getType() const
	{
		return this->type;
	}

	ProjectEventStructure::ChangeType ProjectEventStructure::getChangeType() const
	{
		return this->cType;
	}

	void ProjectEventStructure::setPtr(SerializableProjectStructure* ptr)
	{
		this->ptr.reset(ptr);
	}
}