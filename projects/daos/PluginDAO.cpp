#include "PluginDAO.h"

namespace vocalshaper {
	Plugin::PluginType PluginDAO::getPluginType(const Plugin* ptr)
	{
		if (!ptr) {
			return Plugin::PluginType::Unknown;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->pluginType;
	}

	int PluginDAO::getUniqueId(const Plugin* ptr)
	{
		if (!ptr) {
			return -1;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->uniqueId;
	}

	void PluginDAO::setUniqueId(Plugin* ptr, int uniqueId)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->uniqueId == uniqueId) {
			return;
		}
		ptr->saved = false;
		ptr->uniqueId = uniqueId;
	}

	bool PluginDAO::getEnabled(const Plugin* ptr)
	{
		if (!ptr) {
			return false;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->enabled;
	}

	void PluginDAO::setEnabled(Plugin* ptr, bool enabled)
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

	int PluginDAO::paramSize(const Plugin* ptr)
	{
		if (!ptr) {
			return -1;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->params.size();
	}

	Param* PluginDAO::getParam(const Plugin* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->params[index];
	}

	Param* PluginDAO::insertParam(Plugin* ptr, int index, Param* param)
	{
		if (!ptr || !param) {
			return nullptr;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = false;
		return ptr->params.insert(index, param);
	}

	Param* PluginDAO::releaseParam(Plugin* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = false;
		return ptr->params.removeAndReturn(index);
	}

	bool PluginDAO::isSaved(const Plugin* ptr)
	{
		if (!ptr) {
			return true;
		}
		juce::ScopedReadLock locker(ptr->lock);
		if (!ptr->saved) {
			return false;
		}
		for (auto i : ptr->params) {
			if (!ParamDAO::isSaved(i)) {
				return false;
			}
		}
		return true;
	}

	void PluginDAO::save(Plugin* ptr)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = true;
		for (auto i : ptr->params) {
			ParamDAO::save(i);
		}
	}
}