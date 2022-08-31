#include "ScriptDAO.h"

namespace vocalshaper {
	Script::ScriptType ScriptDAO::getScriptType(const Script* ptr)
	{
		if (!ptr) {
			return Script::ScriptType::Lua;
		}
		return ptr->scriptType;
	}

	void ScriptDAO::setScriptType(Script* ptr, Script::ScriptType type)
	{
		if (!ptr) {
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
		return ptr->data;
	}

	void ScriptDAO::setData(Script* ptr, juce::String data)
	{
		if (!ptr) {
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
		return ptr->enabled;
	}

	void ScriptDAO::setEnabled(Script* ptr, bool enabled)
	{
		if (!ptr) {
			return;
		}
		ptr->saved = false;
		ptr->enabled = enabled;
	}

	bool ScriptDAO::isSaved(const Script* ptr)
	{
		return true;
	}

	void ScriptDAO::save(Script* ptr)
	{

	}

	Script* ScriptDAO::create()
	{
		return new Script;
	}

	void ScriptDAO::destory(Script* ptr)
	{
		delete ptr;
	}
}