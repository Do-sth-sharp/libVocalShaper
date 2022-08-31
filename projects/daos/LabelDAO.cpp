#include "LabelDAO.h"

namespace vocalshaper {
	Label::LabelType LabelDAO::getLabelType(const Label* ptr)
	{
		if (!ptr) {
			return Label::LabelType::Lua;
		}
		return ptr->labelType;
	}

	void LabelDAO::setLabelType(Label* ptr, Label::LabelType type)
	{
		if (!ptr) {
			return;
		}
		ptr->saved = false;
		ptr->labelType = type;
	}

	ProjectTime LabelDAO::getPosition(const Label* ptr)
	{
		if (!ptr) {
			return make_time(0, 0);
		}
		return ptr->position;
	}

	void LabelDAO::setPosition(Label* ptr, ProjectTime time)
	{
		if (!ptr) {
			return;
		}
		ptr->saved = false;
		ptr->position = time;
	}

	juce::String LabelDAO::getData(const Label* ptr)
	{
		if (!ptr) {
			return juce::String();
		}
		return ptr->data;
	}

	void LabelDAO::setData(Label* ptr, juce::String data)
	{
		if (!ptr) {
			return;
		}
		ptr->saved = false;
		ptr->data = data;
	}

	bool LabelDAO::isSaved(const Label* ptr)
	{
		return true;
	}

	void LabelDAO::save(Label* ptr)
	{

	}

	Label* LabelDAO::create()
	{
		return new Label;
	}

	void LabelDAO::destory(Label* ptr)
	{
		delete ptr;
	}
}