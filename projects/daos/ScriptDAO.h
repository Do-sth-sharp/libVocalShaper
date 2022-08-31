#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "../datas/Script.h"

namespace vocalshaper {
	class VSAPI ScriptDAO
	{
		ScriptDAO() = default;

	public:
		static Script::ScriptType getScriptType(const Script* ptr);
		static void setScriptType(Script* ptr, Script::ScriptType type);

		static juce::String getData(const Script* ptr);
		static void setData(Script* ptr, juce::String data);
		static bool getEnabled(const Script* ptr);
		static void setEnabled(Script* ptr, bool enabled);

	public:
		static bool isSaved(const Script* ptr);
		static void save(Script* ptr);

	public:
		static Script* create();
		static void destory(Script* ptr);
	};
}