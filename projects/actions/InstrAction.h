#pragma once
#include "ActionBase.h"

#define VS_CREATE_ROUTINE_INSTR_ACTION(_ActionName, _DataType, _ActionType) \
VS_CREATE_ROUTINE_ACTION(_ActionName, InstrAction, _DataType, _ActionType)

#define VS_CREATE_ROUTINE_INSTR_ACTION_WITH_INDEXED_OBJECT(_ActionName, _DataMemType, _ActionType) \
VS_CREATE_ROUTINE_ACTION_WITH_INDEXED_OBJECT(_ActionName, InstrAction, _DataMemType, _ActionType)

#define VS_INSTR_TARGET_LIST \
int track = 0;

#define VS_INSTR_ACTION_LIST \
UniqueId, \
AddParam, \
RemoveParam

namespace vocalshaper {
	namespace actions {
		VS_CREATE_ROUTINE_ACTION_BASE(InstrAction, InstrTarget, Instr, VS_INSTR_TARGET_LIST, VS_INSTR_ACTION_LIST);

		namespace instr {
			VS_CREATE_ROUTINE_INSTR_ACTION(UniqueIdAction, IntData, UniqueId);

			VS_CREATE_ROUTINE_INSTR_ACTION_WITH_INDEXED_OBJECT(AddParamAction, vocalshaper::Param*, AddParam);
			VS_CREATE_ROUTINE_INSTR_ACTION_WITH_INDEXED_OBJECT(RemoveParamAction, std::nullptr_t, RemoveParam);
		}
	}
}