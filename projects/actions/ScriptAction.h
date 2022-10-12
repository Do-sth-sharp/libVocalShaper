#pragma once
#include "ActionBase.h"

#define VS_CREATE_ROUTINE_SCRIPT_ACTION(_ActionName, _DataType, _ActionType) \
VS_CREATE_ROUTINE_ACTION(_ActionName, ScriptAction, _DataType, _ActionType)

#define VS_CREATE_ROUTINE_SCRIPT_ACTION_WITH_INDEXED_OBJECT(_ActionName, _DataMemType, _ActionType) \
VS_CREATE_ROUTINE_ACTION_WITH_INDEXED_OBJECT(_ActionName, ScriptAction, _DataMemType, _ActionType)

#define VS_SCRIPT_TARGET_LIST \
int script = 0;

#define VS_SCRIPT_ACTION_LIST \
Type, \
Data, \
Enabled

namespace vocalshaper {
	namespace actions {
		VS_CREATE_ROUTINE_ACTION_BASE(ScriptAction, ScriptTarget, Script, VS_SCRIPT_TARGET_LIST, VS_SCRIPT_ACTION_LIST);

		namespace script {
			VS_CREATE_ROUTINE_SCRIPT_ACTION(TypeAction, ScriptTypeData, Type);
			VS_CREATE_ROUTINE_SCRIPT_ACTION(DataAction, StringData, Data);
			VS_CREATE_ROUTINE_SCRIPT_ACTION(EnabledAction, BoolData, Enabled);
		}
	}
}