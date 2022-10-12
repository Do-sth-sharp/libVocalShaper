#pragma once
#include "ActionBase.h"

#define VS_CREATE_ROUTINE_DPOINT_ACTION(_ActionName, _DataType, _ActionType) \
VS_CREATE_ROUTINE_ACTION(_ActionName, DPointAction, _DataType, _ActionType)

#define VS_CREATE_ROUTINE_DPOINT_ACTION_WITH_INDEXED_OBJECT(_ActionName, _DataMemType, _ActionType) \
VS_CREATE_ROUTINE_ACTION_WITH_INDEXED_OBJECT(_ActionName, DPointAction, _DataMemType, _ActionType)

#define VS_DPOINT_TARGET_LIST \
int track = 0; \
int curve = 0; \
int dpoint = 0;

#define VS_DPOINT_ACTION_LIST \
X, \
Y, \
Dl, \
Dr

namespace vocalshaper {
	namespace actions {
		VS_CREATE_ROUTINE_ACTION_BASE(DPointAction, DPointTarget, DPoint, VS_DPOINT_TARGET_LIST, VS_DPOINT_ACTION_LIST);

		namespace dpoint {
			VS_CREATE_ROUTINE_DPOINT_ACTION(XAction, TimeData, X);
			VS_CREATE_ROUTINE_DPOINT_ACTION(YAction, DoubleData, Y);
			VS_CREATE_ROUTINE_DPOINT_ACTION(DlAction, DoubleData, Dl);
			VS_CREATE_ROUTINE_DPOINT_ACTION(DrAction, DoubleData, Dr);
		}
	}
}