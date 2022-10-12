#pragma once
#include "ActionBase.h"

#define VS_CREATE_ROUTINE_LABEL_ACTION(_ActionName, _DataType, _ActionType) \
VS_CREATE_ROUTINE_ACTION(_ActionName, LabelAction, _DataType, _ActionType)

#define VS_CREATE_ROUTINE_LABEL_ACTION_WITH_INDEXED_OBJECT(_ActionName, _DataMemType, _ActionType) \
VS_CREATE_ROUTINE_ACTION_WITH_INDEXED_OBJECT(_ActionName, LabelAction, _DataMemType, _ActionType)

#define VS_LABEL_TARGET_LIST \
int label = 0;

#define VS_LABEL_ACTION_LIST \
Type, \
Position, \
Data

namespace vocalshaper {
	namespace actions {
		VS_CREATE_ROUTINE_ACTION_BASE(LabelAction, LabelTarget, Label, VS_LABEL_TARGET_LIST, VS_LABEL_ACTION_LIST);

		namespace label {
			VS_CREATE_ROUTINE_LABEL_ACTION(TypeAction, LabelTypeData, Type);
			VS_CREATE_ROUTINE_LABEL_ACTION(PositionAction, TimeData, Position);
			VS_CREATE_ROUTINE_LABEL_ACTION(DataAction, StringData, Data);
		}
	}
}