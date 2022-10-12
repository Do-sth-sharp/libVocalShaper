#include "InstrAction.h"
#include "../daos/ProjectDAO.h"
#include "../ProjectProxy.h"

#define VS_CREATE_ROUTINE_INSTR_DATA_SWAP_METHOD(_MethodName, _DataMemType, _DAOGetMethodName, _DAOSetMethodName) \
VS_CREATE_ROUTINE_DATA_SWAP_METHOD(_MethodName, Instr, _DataMemType, InstrDAO, _DAOGetMethodName, _DAOSetMethodName)

#define VS_CREATE_ROUTINE_INSTR_DATA_ADD_METHOD(_MethodName, _SubObjectPtrType, _DAOAddMethodName) \
VS_CREATE_ROUTINE_DATA_ADD_METHOD(_MethodName, Instr, _SubObjectPtrType, InstrDAO, _DAOAddMethodName)

#define VS_CREATE_ROUTINE_INSTR_DATA_REMOVE_METHOD(_MethodName, _SubObjectPtrType, _DAORemoveMethodName) \
VS_CREATE_ROUTINE_DATA_REMOVE_METHOD(_MethodName, Instr, _SubObjectPtrType, InstrDAO, _DAORemoveMethodName)

#define VS_INSTR_SELECT \
TrackDAO::getInstrument(ProjectDAO::getTrack(ptr, target->track))

namespace vocalshaper {
	namespace actions {
		namespace instr {
			VS_CREATE_ROUTINE_INSTR_DATA_SWAP_METHOD(swapUniqueId, int, getUniqueId, setUniqueId);

			VS_CREATE_ROUTINE_INSTR_DATA_ADD_METHOD(addParam, Param, insertParam);
			VS_CREATE_ROUTINE_INSTR_DATA_REMOVE_METHOD(removeParam, Param, releaseParam);

			VS_CREATE_OBJECT_SELECT_METHOD_BY_ACTION(selectInstr, Instr, InstrAction, VS_INSTR_SELECT);

			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(UniqueIdAction, selectInstr, swapUniqueId);

			VS_CREATE_ADD_ROUTINE_DATA_ACTION_DEFINEITION(AddParamAction, selectInstr, addParam, removeParam);
			VS_CREATE_REMOVE_ROUTINE_DATA_ACTION_DEFINEITION(RemoveParamAction, selectInstr, addParam, removeParam);
		}
	}
}
