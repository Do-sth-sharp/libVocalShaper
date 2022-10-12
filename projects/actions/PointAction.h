#pragma once
#include "ActionBase.h"

#define VS_CREATE_ROUTINE_POINT_ACTION(_ActionName, _DataType, _ActionType) \
VS_CREATE_ROUTINE_ACTION(_ActionName, PointAction, _DataType, _ActionType)

#define VS_CREATE_ROUTINE_POINT_ACTION_WITH_INDEXED_OBJECT(_ActionName, _DataMemType, _ActionType) \
VS_CREATE_ROUTINE_ACTION_WITH_INDEXED_OBJECT(_ActionName, PointAction, _DataMemType, _ActionType)

#define VS_POINT_TARGET_LIST \
int track = 0; \
int note = 0; \
int phoneme = 0; \
int point = 0;

#define VS_POINT_ACTION_LIST \
X, \
Y

namespace vocalshaper {
	namespace actions {
		VS_CREATE_ROUTINE_ACTION_BASE(PointAction, PointTarget, Point, VS_POINT_TARGET_LIST, VS_POINT_ACTION_LIST);

		namespace point {
			VS_CREATE_ROUTINE_POINT_ACTION(XAction, DoubleData, X);
			VS_CREATE_ROUTINE_POINT_ACTION(YAction, DoubleData, Y);
		}
	}
}