#include "PluginDAO.h"

namespace vocalshaper {
	Plugin::PluginType PluginDAO::getPluginType(const Plugin* ptr)
	{
		if (!ptr) {
			return Plugin::PluginType::Unknown;
		}
		return ptr->pluginType;
	}

	int PluginDAO::getUniqueId(const Plugin* ptr)
	{
		if (!ptr) {
			return -1;
		}
		return ptr->uniqueId;
	}

	void PluginDAO::setUniqueId(Plugin* ptr, int uniqueId)
	{
		if (!ptr) {
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
		return ptr->enabled;
	}

	void PluginDAO::setEnabled(Plugin* ptr, bool enabled)
	{
		if (!ptr) {
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
		return ptr->params.size();
	}

	Param* PluginDAO::getParam(const Plugin* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		return ptr->params[index];
	}

	Param* PluginDAO::insertParam(Plugin* ptr, int index, Param* param)
	{
		if (!ptr || !param) {
			return nullptr;
		}
		ptr->saved = false;
		return ptr->params.insert(index, param);
	}

	Param* PluginDAO::releaseParam(Plugin* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		ptr->saved = false;
		return ptr->params.removeAndReturn(index);
	}

	bool PluginDAO::isSaved(const Plugin* ptr)
	{
		return true;
	}

	void PluginDAO::save(Plugin* ptr)
	{

	}

	Plugin* PluginDAO::create(Plugin::PluginType type)
	{
		auto ptr = new Plugin;
		ptr->pluginType = type;
		return ptr;
	}

	void PluginDAO::destory(Plugin* ptr)
	{
		delete ptr;
	}
}