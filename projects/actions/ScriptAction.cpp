#include "ScriptAction.h"
#include "../daos/ProjectDAO.h"
#include "../ProjectProxy.h"

#define VS_CREATE_ROUTINE_SCRIPT_DATA_SWAP_METHOD(_MethodName, _DataMemType, _DAOGetMethodName, _DAOSetMethodName) \
VS_CREATE_ROUTINE_DATA_SWAP_METHOD(_MethodName, Script, _DataMemType, ScriptDAO, _DAOGetMethodName, _DAOSetMethodName)

#define VS_CREATE_ROUTINE_SCRIPT_DATA_ADD_METHOD(_MethodName, _SubObjectPtrType, _DAOAddMethodName) \
VS_CREATE_ROUTINE_DATA_ADD_METHOD(_MethodName, Script, _SubObjectPtrType, ScriptDAO, _DAOAddMethodName)

#define VS_CREATE_ROUTINE_SCRIPT_DATA_REMOVE_METHOD(_MethodName, _SubObjectPtrType, _DAORemoveMethodName) \
VS_CREATE_ROUTINE_DATA_REMOVE_METHOD(_MethodName, Script, _SubObjectPtrType, ScriptDAO, _DAORemoveMethodName)

#define VS_SCRIPT_SELECT \
ProjectDAO::getScript(ptr, target->script)

namespace vocalshaper {
	namespace actions {
		namespace script {
			VS_CREATE_ROUTINE_SCRIPT_DATA_SWAP_METHOD(swapType, vocalshaper::Script::ScriptType, getScriptType, setScriptType);
			VS_CREATE_ROUTINE_SCRIPT_DATA_SWAP_METHOD(swapData, juce::String, getData, setData);
			VS_CREATE_ROUTINE_SCRIPT_DATA_SWAP_METHOD(swapEnabled, bool, getEnabled, setEnabled);

			VS_CREATE_OBJECT_SELECT_METHOD_BY_ACTION(selectScript, Script, ScriptAction, VS_SCRIPT_SELECT);

			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(TypeAction, selectScript, swapType);
			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(DataAction, selectScript, swapData);
			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(EnabledAction, selectScript, swapEnabled);
		}
	}
}