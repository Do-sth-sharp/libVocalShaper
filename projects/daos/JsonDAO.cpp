#include "JsonDAO.h"

namespace vocalshaper {
	const juce::var* JsonDAO::getData(const Json* ptr)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return &(ptr->data);
	}

	juce::var* JsonDAO::getDataMutable(Json* ptr)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = false;
		return &(ptr->data);
	}

	bool JsonDAO::isSaved(const Json* ptr)
	{
		if (!ptr) {
			return true;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->saved;
	}

	void JsonDAO::save(Json* ptr)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = true;
	}

	Json* JsonDAO::create()
	{
		return new Json;
	}

	void JsonDAO::destory(Json* ptr)
	{
		delete ptr;
	}
}