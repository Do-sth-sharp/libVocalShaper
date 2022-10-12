#pragma once
#include "ActionBase.h"

#define VS_CREATE_ROUTINE_PLUGINPARAM_ACTION(_ActionName, _DataType, _ActionType) \
VS_CREATE_ROUTINE_ACTION(_ActionName, PluginParamAction, _DataType, _ActionType)

#define VS_CREATE_ROUTINE_PLUGINPARAM_ACTION_WITH_INDEXED_OBJECT(_ActionName, _DataMemType, _ActionType) \
VS_CREATE_ROUTINE_ACTION_WITH_INDEXED_OBJECT(_ActionName, PluginParamAction, _DataMemType, _ActionType)

#define VS_PLUGINPARAM_TARGET_LIST \
int track = 0; \
int plugin = 0; \
int param = 0;

#define VS_PLUGINPARAM_ACTION_LIST \
Id, \
BoolData, \
ChoiceData, \
FloatData, \
IntData, \
Controler

namespace vocalshaper {
	namespace actions {
		VS_CREATE_ROUTINE_ACTION_BASE(PluginParamAction, PluginParamTarget, PluginParam, VS_PLUGINPARAM_TARGET_LIST, VS_PLUGINPARAM_ACTION_LIST);

		namespace pluginparam {
			VS_CREATE_ROUTINE_PLUGINPARAM_ACTION(IdAction, StringData, Id);
			VS_CREATE_ROUTINE_PLUGINPARAM_ACTION(BoolDataAction, BoolData, BoolData);
			VS_CREATE_ROUTINE_PLUGINPARAM_ACTION(ChoiceDataAction, IntData, ChoiceData);
			VS_CREATE_ROUTINE_PLUGINPARAM_ACTION(FloatDataAction, FloatData, FloatData);
			VS_CREATE_ROUTINE_PLUGINPARAM_ACTION(IntDataAction, IntData, IntData);
			VS_CREATE_ROUTINE_PLUGINPARAM_ACTION(ControlerAction, StringData, Controler);
		}
	}
}