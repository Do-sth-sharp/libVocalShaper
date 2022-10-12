#pragma once
#include "ActionBase.h"

#define VS_CREATE_ROUTINE_NOTEPARAM_ACTION(_ActionName, _DataType, _ActionType) \
VS_CREATE_ROUTINE_ACTION(_ActionName, NoteParamAction, _DataType, _ActionType)

#define VS_CREATE_ROUTINE_NOTEPARAM_ACTION_WITH_INDEXED_OBJECT(_ActionName, _DataMemType, _ActionType) \
VS_CREATE_ROUTINE_ACTION_WITH_INDEXED_OBJECT(_ActionName, NoteParamAction, _DataMemType, _ActionType)

#define VS_NOTEPARAM_TARGET_LIST \
int track = 0; \
int note = 0; \
int param = 0;

#define VS_NOTEPARAM_ACTION_LIST \
Id, \
BoolData, \
ChoiceData, \
FloatData, \
IntData, \
Controler

namespace vocalshaper {
	namespace actions {
		VS_CREATE_ROUTINE_ACTION_BASE(NoteParamAction, NoteParamTarget, NoteParam, VS_NOTEPARAM_TARGET_LIST, VS_NOTEPARAM_ACTION_LIST);

		namespace noteparam {
			VS_CREATE_ROUTINE_NOTEPARAM_ACTION(IdAction, StringData, Id);
			VS_CREATE_ROUTINE_NOTEPARAM_ACTION(BoolDataAction, BoolData, BoolData);
			VS_CREATE_ROUTINE_NOTEPARAM_ACTION(ChoiceDataAction, IntData, ChoiceData);
			VS_CREATE_ROUTINE_NOTEPARAM_ACTION(FloatDataAction, FloatData, FloatData);
			VS_CREATE_ROUTINE_NOTEPARAM_ACTION(IntDataAction, IntData, IntData);
			VS_CREATE_ROUTINE_NOTEPARAM_ACTION(ControlerAction, StringData, Controler);
		}
	}
}