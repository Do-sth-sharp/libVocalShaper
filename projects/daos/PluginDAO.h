#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "../datas/Plugin.h"
#include "ParamDAO.h"

namespace vocalshaper {
	class VSAPI PluginDAO
	{
		PluginDAO() = default;

	public:
		static Plugin::PluginType getPluginType(const Plugin* ptr);

		static int getUniqueId(const Plugin* ptr);
		static void setUniqueId(Plugin* ptr, int uniqueId);
		static bool getEnabled(const Plugin* ptr);
		static void setEnabled(Plugin* ptr, bool enabled);

		static int paramSize(const Plugin* ptr);
		static Param* getParam(const Plugin* ptr, int index);
		static Param* insertParam(Plugin* ptr, int index, Param* param);
		static Param* releaseParam(Plugin* ptr, int index);

	public:
		static bool isSaved(const Plugin* ptr);
		static void save(Plugin* ptr);

	public:
		static Plugin* create(Plugin::PluginType type);
		static void destory(Plugin* ptr);
	};
}