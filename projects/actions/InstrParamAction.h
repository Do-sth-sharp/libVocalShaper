#pragma once
#include "ActionBase.h"

#define VS_CREATE_ROUTINE_INSTRPARAM_ACTION(_ActionName, _DataType, _ActionType) \
VS_CREATE_ROUTINE_ACTION(_ActionName, InstrParamAction, _DataType, _ActionType)

#define VS_CREATE_ROUTINE_INSTRPARAM_ACTION_WITH_INDEXED_OBJECT(_ActionName, _DataMemType, _ActionType) \
VS_CREATE_ROUTINE_ACTION_WITH_INDEXED_OBJECT(_ActionName, InstrParamAction, _DataMemType, _ActionType)

#define VS_INSTRPARAM_TARGET_LIST \
int track = 0; \
int param = 0;

#define VS_INSTRPARAM_ACTION_LIST \
Id, \
BoolData, \
ChoiceData, \
FloatData, \
IntData, \
Controler

namespace vocalshaper {
	namespace actions {
		VS_CREATE_ROUTINE_ACTION_BASE(InstrParamAction, InstrParamTarget, InstrParam, VS_INSTRPARAM_TARGET_LIST, VS_INSTRPARAM_ACTION_LIST);

		namespace instrparam {
			VS_CREATE_ROUTINE_INSTRPARAM_ACTION(IdAction, StringData, Id);
			VS_CREATE_ROUTINE_INSTRPARAM_ACTION(BoolDataAction, BoolData, BoolData);
			VS_CREATE_ROUTINE_INSTRPARAM_ACTION(ChoiceDataAction, IntData, ChoiceData);
			VS_CREATE_ROUTINE_INSTRPARAM_ACTION(FloatDataAction, FloatData, FloatData);
			VS_CREATE_ROUTINE_INSTRPARAM_ACTION(IntDataAction, IntData, IntData);
			VS_CREATE_ROUTINE_INSTRPARAM_ACTION(ControlerAction, StringData, Controler);
		}
	}
}