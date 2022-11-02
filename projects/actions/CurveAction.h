#pragma once
#include "ActionBase.h"

#define VS_CREATE_ROUTINE_CURVE_ACTION(_ActionName, _DataType, _ActionType) \
VS_CREATE_ROUTINE_ACTION(_ActionName, CurveAction, _DataType, _ActionType)

#define VS_CREATE_ROUTINE_CURVE_ACTION_WITH_INDEXED_OBJECT(_ActionName, _DataMemType, _ActionType) \
VS_CREATE_ROUTINE_ACTION_WITH_INDEXED_OBJECT(_ActionName, CurveAction, _DataMemType, _ActionType)

#define VS_CURVE_TARGET_LIST \
int track = 0; \
int curve = 0;

#define VS_CURVE_ACTION_LIST \
Id, \
AddDPoint, \
RemoveDPoint

namespace vocalshaper {
	namespace actions {
		VS_CREATE_ROUTINE_ACTION_BASE(CurveAction, CurveTarget, Curve, VS_CURVE_TARGET_LIST, VS_CURVE_ACTION_LIST);

		namespace curve {
			VS_CREATE_ROUTINE_CURVE_ACTION(IdAction, StringData, Id);

			VS_CREATE_ROUTINE_CURVE_ACTION_WITH_INDEXED_OBJECT(AddDPointAction, vocalshaper::DPoint*, AddDPoint);
			VS_CREATE_ROUTINE_CURVE_ACTION_WITH_INDEXED_OBJECT(RemoveDPointAction, std::nullptr_t, RemoveDPoint);
		}
	}
}