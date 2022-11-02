#pragma once
#include "ActionBase.h"

#define VS_CREATE_ROUTINE_PLUGIN_ACTION(_ActionName, _DataType, _ActionType) \
VS_CREATE_ROUTINE_ACTION(_ActionName, PluginAction, _DataType, _ActionType)

#define VS_CREATE_ROUTINE_PLUGIN_ACTION_WITH_INDEXED_OBJECT(_ActionName, _DataMemType, _ActionType) \
VS_CREATE_ROUTINE_ACTION_WITH_INDEXED_OBJECT(_ActionName, PluginAction, _DataMemType, _ActionType)

#define VS_PLUGIN_TARGET_LIST \
int track = 0; \
int plugin = 0;

#define VS_PLUGIN_ACTION_LIST \
UniqueId, \
Enabled, \
AddParam, \
RemoveParam

namespace vocalshaper {
	namespace actions {
		VS_CREATE_ROUTINE_ACTION_BASE(PluginAction, PluginTarget, Plugin, VS_PLUGIN_TARGET_LIST, VS_PLUGIN_ACTION_LIST);

		namespace plugin {
			VS_CREATE_ROUTINE_PLUGIN_ACTION(UniqueIdAction, IntData, UniqueId);
			VS_CREATE_ROUTINE_PLUGIN_ACTION(EnabledAction, BoolData, Enabled);

			VS_CREATE_ROUTINE_PLUGIN_ACTION_WITH_INDEXED_OBJECT(AddParamAction, vocalshaper::Param*, AddParam);
			VS_CREATE_ROUTINE_PLUGIN_ACTION_WITH_INDEXED_OBJECT(RemoveParamAction, std::nullptr_t, RemoveParam);
		}
	}
}