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

	ProjectEventStructure::UndoFlagType ProjectEventStructure::getUndoFlag() const
	{
		return this->undoFlag;
	}

	void ProjectEventStructure::addCallBack(CallBackFunction callback)
	{
		this->callbackList.add(callback);
	}

	void ProjectEventStructure::reverse()
	{
		switch (this->cType)
		{
		case ChangeType::Add:
			this->cType = ChangeType::Remove;
			break;
		case ChangeType::Edit:
			break;
		case ChangeType::Remove:
			this->cType = ChangeType::Add;
			break;
		}

		switch (this->undoFlag)
		{
		case UndoFlagType::Empty:
			this->undoFlag = UndoFlagType::Undo;
			break;
		case UndoFlagType::Undo:
			this->undoFlag = UndoFlagType::Redo;
			break;
		case UndoFlagType::Redo:
			this->undoFlag = UndoFlagType::Undo;
			break;
		}
	}
}