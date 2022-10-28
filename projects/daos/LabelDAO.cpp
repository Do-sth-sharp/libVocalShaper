#include "LabelDAO.h"

namespace vocalshaper {
	Label::LabelType LabelDAO::getLabelType(const Label* ptr)
	{
		if (!ptr) {
			return Label::LabelType::Lua;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->labelType;
	}

	void LabelDAO::setLabelType(Label* ptr, Label::LabelType type)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->labelType == type) {
			return;
		}
		ptr->saved = false;
		ptr->labelType = type;
	}

	double LabelDAO::getPosition(const Label* ptr)
	{
		if (!ptr) {
			return 0;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->position;
	}

	void LabelDAO::setPosition(Label* ptr, double time)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->position == time) {
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
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->data;
	}

	void LabelDAO::setData(Label* ptr, juce::String data)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->data == data) {
			return;
		}
		ptr->saved = false;
		ptr->data = data;
	}

	bool LabelDAO::isSaved(const Label* ptr)
	{
		if (!ptr) {
			return true;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->saved;
	}

	void LabelDAO::save(Label* ptr)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = true;
	}
}