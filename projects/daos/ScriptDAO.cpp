#include "ScriptDAO.h"

namespace vocalshaper {
	Script::ScriptType ScriptDAO::getScriptType(const Script* ptr)
	{
		if (!ptr) {
			return Script::ScriptType::Lua;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->scriptType;
	}

	void ScriptDAO::setScriptType(Script* ptr, Script::ScriptType type)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->scriptType == type) {
			return;
		}
		ptr->saved = false;
		ptr->scriptType = type;
	}

	juce::String ScriptDAO::getData(const Script* ptr)
	{
		if (!ptr) {
			return juce::String();
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->data;
	}

	void ScriptDAO::setData(Script* ptr, juce::String data)
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

	bool ScriptDAO::getEnabled(const Script* ptr)
	{
		if (!ptr) {
			return false;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->enabled;
	}

	void ScriptDAO::setEnabled(Script* ptr, bool enabled)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->enabled == enabled) {
			return;
		}
		ptr->saved = false;
		ptr->enabled = enabled;
	}

	bool ScriptDAO::isSaved(const Script* ptr)
	{
		if (!ptr) {
			return true;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->saved;
	}

	void ScriptDAO::save(Script* ptr)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = true;
	}
}