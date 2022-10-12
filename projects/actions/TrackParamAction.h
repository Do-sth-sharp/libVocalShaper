#pragma once
#include "ActionBase.h"

#define VS_CREATE_ROUTINE_TRACKPARAM_ACTION(_ActionName, _DataType, _ActionType) \
VS_CREATE_ROUTINE_ACTION(_ActionName, TrackParamAction, _DataType, _ActionType)

#define VS_CREATE_ROUTINE_TRACKPARAM_ACTION_WITH_INDEXED_OBJECT(_ActionName, _DataMemType, _ActionType) \
VS_CREATE_ROUTINE_ACTION_WITH_INDEXED_OBJECT(_ActionName, TrackParamAction, _DataMemType, _ActionType)

#define VS_TRACKPARAM_TARGET_LIST \
int track = 0; \
int param = 0;

#define VS_TRACKPARAM_ACTION_LIST \
Id, \
BoolData, \
ChoiceData, \
FloatData, \
IntData, \
Controler

namespace vocalshaper {
	namespace actions {
		VS_CREATE_ROUTINE_ACTION_BASE(TrackParamAction, TrackParamTarget, TrackParam, VS_TRACKPARAM_TARGET_LIST, VS_TRACKPARAM_ACTION_LIST);

		namespace trackparam {
			VS_CREATE_ROUTINE_TRACKPARAM_ACTION(IdAction, StringData, Id);
			VS_CREATE_ROUTINE_TRACKPARAM_ACTION(BoolDataAction, BoolData, BoolData);
			VS_CREATE_ROUTINE_TRACKPARAM_ACTION(ChoiceDataAction, IntData, ChoiceData);
			VS_CREATE_ROUTINE_TRACKPARAM_ACTION(FloatDataAction, FloatData, FloatData);
			VS_CREATE_ROUTINE_TRACKPARAM_ACTION(IntDataAction, IntData, IntData);
			VS_CREATE_ROUTINE_TRACKPARAM_ACTION(ControlerAction, StringData, Controler);
		}
	}
}