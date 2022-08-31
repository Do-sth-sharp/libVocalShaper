#include "ParamDAO.h"

namespace vocalshaper {
	Param::ParamType ParamDAO::getParamType(const Param* ptr)
	{
		if (!ptr) {
			return Param::ParamType::Empty;
		}
		return ptr->paramType;
	}

	juce::String ParamDAO::getId(const Param* ptr)
	{
		if (!ptr) {
			return juce::String();
		}
		return ptr->id;
	}

	void ParamDAO::setId(Param* ptr, juce::String id)
	{
		if (!ptr) {
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

	bool ParamDAO::setBoolData(const Param* ptr, bool value)
	{
		if (!ptr) {
			return false;
		}
		if (ptr->paramType != Param::ParamType::Bool) {
			return false;
		}
		ptr->saved = false;
		ptr->value.boolData = value;
		return true;
	}

	bool ParamDAO::setChoiceData(const Param* ptr, int value)
	{
		if (!ptr) {
			return false;
		}
		if (ptr->paramType != Param::ParamType::Choice) {
			return false;
		}
		ptr->saved = false;
		ptr->value.choiceData = value;
		return true;
	}

	bool ParamDAO::setFloatData(const Param* ptr, float value)
	{
		if (!ptr) {
			return false;
		}
		if (ptr->paramType != Param::ParamType::Float) {
			return false;
		}
		ptr->saved = false;
		ptr->value.floatData = value;
		return true;
	}

	bool ParamDAO::setIntData(const Param* ptr, int value)
	{
		if (!ptr) {
			return false;
		}
		if (ptr->paramType != Param::ParamType::Int) {
			return false;
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
		return ptr->controler;
	}

	void ParamDAO::setControler(Param* ptr, juce::String controler)
	{
		if (!ptr) {
			return;
		}
		ptr->saved = false;
		ptr->controler = controler;
	}

	bool ParamDAO::isSaved(const Param* ptr)
	{
		reutrn true;
	}

	void ParamDAO::save(Param* ptr)
	{

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