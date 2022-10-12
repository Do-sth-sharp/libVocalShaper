#include "PluginAction.h"
#include "../daos/ProjectDAO.h"
#include "../ProjectProxy.h"

#define VS_CREATE_ROUTINE_PLUGIN_DATA_SWAP_METHOD(_MethodName, _DataMemType, _DAOGetMethodName, _DAOSetMethodName) \
VS_CREATE_ROUTINE_DATA_SWAP_METHOD(_MethodName, Plugin, _DataMemType, PluginDAO, _DAOGetMethodName, _DAOSetMethodName)

#define VS_CREATE_ROUTINE_PLUGIN_DATA_ADD_METHOD(_MethodName, _SubObjectPtrType, _DAOAddMethodName) \
VS_CREATE_ROUTINE_DATA_ADD_METHOD(_MethodName, Plugin, _SubObjectPtrType, PluginDAO, _DAOAddMethodName)

#define VS_CREATE_ROUTINE_PLUGIN_DATA_REMOVE_METHOD(_MethodName, _SubObjectPtrType, _DAORemoveMethodName) \
VS_CREATE_ROUTINE_DATA_REMOVE_METHOD(_MethodName, Plugin, _SubObjectPtrType, PluginDAO, _DAORemoveMethodName)

#define VS_PLUGIN_SELECT (target->track == -1) \
? TrackDAO::getPlugin(ProjectDAO::getMasterTrack(ptr), target->plugin) \
: TrackDAO::getPlugin(ProjectDAO::getTrack(ptr, target->track), target->plugin)

namespace vocalshaper {
	namespace actions {
		namespace plugin {
			VS_CREATE_ROUTINE_PLUGIN_DATA_SWAP_METHOD(swapUniqueId, int, getUniqueId, setUniqueId);
			VS_CREATE_ROUTINE_PLUGIN_DATA_SWAP_METHOD(swapEnabled, bool, getEnabled, setEnabled);

			VS_CREATE_ROUTINE_PLUGIN_DATA_ADD_METHOD(addParam, Param, insertParam);
			VS_CREATE_ROUTINE_PLUGIN_DATA_REMOVE_METHOD(removeParam, Param, releaseParam);

			VS_CREATE_OBJECT_SELECT_METHOD_BY_ACTION(selectPlugin, Plugin, PluginAction, VS_PLUGIN_SELECT);

			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(UniqueIdAction, selectPlugin, swapUniqueId);
			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(EnabledAction, selectPlugin, swapEnabled);

			VS_CREATE_ADD_ROUTINE_DATA_ACTION_DEFINEITION(AddParamAction, selectPlugin, addParam, removeParam);
			VS_CREATE_REMOVE_ROUTINE_DATA_ACTION_DEFINEITION(RemoveParamAction, selectPlugin, addParam, removeParam);
		}
	}
}
