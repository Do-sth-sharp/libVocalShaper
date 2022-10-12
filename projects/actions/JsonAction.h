#pragma once
#include "ActionBase.h"

#define VS_CREATE_ROUTINE_JSON_ACTION(_ActionName, _DataType, _ActionType) \
VS_CREATE_ROUTINE_ACTION(_ActionName, JsonAction, _DataType, _ActionType)

#define VS_CREATE_ROUTINE_JSON_ACTION_WITH_INDEXED_OBJECT(_ActionName, _DataMemType, _ActionType) \
VS_CREATE_ROUTINE_ACTION_WITH_INDEXED_OBJECT(_ActionName, JsonAction, _DataMemType, _ActionType)

#define VS_JSON_TARGET_LIST \
int json = 0;

#define VS_JSON_ACTION_LIST \
Data

namespace vocalshaper {
	namespace actions {
		VS_CREATE_ROUTINE_ACTION_BASE(JsonAction, JsonTarget, Json, VS_JSON_TARGET_LIST, VS_JSON_ACTION_LIST);

		namespace json {
			VS_CREATE_ROUTINE_JSON_ACTION(DataAction, StringData, Data);
		}
	}
}