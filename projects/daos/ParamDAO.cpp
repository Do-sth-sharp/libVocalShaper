#include "ParamDAO.h"

namespace vocalshaper {
	Param::ParamType ParamDAO::getParamType(const Param* ptr)
	{
		if (!ptr) {
			return Param::ParamType::Empty;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->paramType;
	}

	juce::String ParamDAO::getId(const Param* ptr)
	{
		if (!ptr) {
			return juce::String();
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->id;
	}

	void ParamDAO::setId(Param* ptr, juce::String id)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->id == id) {
			return;
		}
		ptr->saved = false;
		ptr->id = id;
	}

	bool ParamDAO::getBoolData(const Param* ptr)
	{
		if (!ptr) {
			return false;
		}
		juce::ScopedReadLock locker(ptr->lock);
		switch (ptr->paramType)
		{
		case Param::ParamType::Bool:
			return ptr->value.boolData;
		case Param::ParamType::Choice:
			return ptr->value.choiceData;
		case Param::ParamType::Float:
			return ptr->value.floatData;
		case Param::ParamType::Int:
			return ptr->value.intData;
		default:
			return false;
		}
	}

	int ParamDAO::getChoiceData(const Param* ptr)
	{
		if (!ptr) {
			return -1;
		}
		juce::ScopedReadLock locker(ptr->lock);
		switch (ptr->paramType)
		{
		case Param::ParamType::Bool:
			return ptr->value.boolData;
		case Param::ParamType::Choice:
			return ptr->value.choiceData;
		case Param::ParamType::Float:
			return ptr->value.floatData;
		case Param::ParamType::Int:
			return ptr->value.intData;
		default:
			return -1;
		}
	}

	float ParamDAO::getFloatData(const Param* ptr)
	{
		if (!ptr) {
			return 0.f;
		}
		juce::ScopedReadLock locker(ptr->lock);
		switch (ptr->paramType)
		{
		case Param::ParamType::Bool:
			return ptr->value.boolData;
		case Param::ParamType::Choice:
			return ptr->value.choiceData;
		case Param::ParamType::Float:
			return ptr->value.floatData;
		case Param::ParamType::Int:
			return ptr->value.intData;
		default:
			return 0.f;
		}
	}

	int ParamDAO::getIntData(const Param* ptr)
	{
		if (!ptr) {
			return 0;
		}
		juce::ScopedReadLock locker(ptr->lock);
		switch (ptr->paramType)
		{
		case Param::ParamType::Bool:
			return ptr->value.boolData;
		case Param::ParamType::Choice:
			return ptr->value.choiceData;
		case Param::ParamType::Float:
			return ptr->value.floatData;
		case Param::ParamType::Int:
			return ptr->value.intData;
		default:
			return 0;
		}
	}

	bool ParamDAO::setBoolData(Param* ptr, bool value)
	{
		if (!ptr) {
			return false;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->paramType != Param::ParamType::Bool) {
			return false;
		}
		if (ptr->value.boolData == value) {
			return true;
		}
		ptr->saved = false;
		ptr->value.boolData = value;
		return true;
	}

	bool ParamDAO::setChoiceData(Param* ptr, int value)
	{
		if (!ptr) {
			return false;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->paramType != Param::ParamType::Choice) {
			return false;
		}
		if (ptr->value.choiceData == value) {
			return true;
		}
		ptr->saved = false;
		ptr->value.choiceData = value;
		return true;
	}

	bool ParamDAO::setFloatData(Param* ptr, float value)
	{
		if (!ptr) {
			return false;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->paramType != Param::ParamType::Float) {
			return false;
		}
		if (ptr->value.floatData == value) {
			return true;
		}
		ptr->saved = false;
		ptr->value.floatData = value;
		return true;
	}

	bool ParamDAO::setIntData(Param* ptr, int value)
	{
		if (!ptr) {
			return false;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->paramType != Param::ParamType::Int) {
			return false;
		}
		if (ptr->value.intData == value) {
			return true;
		}
		ptr->saved = false;
		ptr->value.intData = value;
		return true;
	}

	juce::String ParamDAO::getControler(const Param* ptr)
	{
		if (!ptr) {
			return juce::String();
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->controler;
	}

	void ParamDAO::setControler(Param* ptr, juce::String controler)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->controler == controler) {
			return;
		}
		ptr->saved = false;
		ptr->controler = controler;
	}

	bool ParamDAO::isSaved(const Param* ptr)
	{
		if (!ptr) {
			return true;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->saved;
	}

	void ParamDAO::save(Param* ptr)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = true;
	}

	Param* ParamDAO::create(Param::ParamType type)
	{
		auto ptr = new Param;
		ptr->paramType = type;
		return ptr;
	}

	void ParamDAO::destory(Param* ptr)
	{
		delete ptr;
	}
}