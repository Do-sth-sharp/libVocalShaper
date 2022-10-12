#include "NoteParamAction.h"
#include "../daos/ProjectDAO.h"
#include "../ProjectProxy.h"

#define VS_CREATE_ROUTINE_PARAM_DATA_SWAP_METHOD(_MethodName, _DataMemType, _DAOGetMethodName, _DAOSetMethodName) \
VS_CREATE_ROUTINE_DATA_SWAP_METHOD(_MethodName, Param, _DataMemType, ParamDAO, _DAOGetMethodName, _DAOSetMethodName)

#define VS_CREATE_ROUTINE_PARAM_DATA_ADD_METHOD(_MethodName, _SubObjectPtrType, _DAOAddMethodName) \
VS_CREATE_ROUTINE_DATA_ADD_METHOD(_MethodName, Param, _SubObjectPtrType, ParamDAO, _DAOAddMethodName)

#define VS_CREATE_ROUTINE_PARAM_DATA_REMOVE_METHOD(_MethodName, _SubObjectPtrType, _DAORemoveMethodName) \
VS_CREATE_ROUTINE_DATA_REMOVE_METHOD(_MethodName, Param, _SubObjectPtrType, ParamDAO, _DAORemoveMethodName)

#define VS_NOTEPARAM_SELECT \
NoteDAO::getParam(TrackDAO::getNote(ProjectDAO::getTrack(ptr, target->track), target->note), target->param)

namespace vocalshaper {
	namespace actions {
		namespace noteparam {
			VS_CREATE_ROUTINE_PARAM_DATA_SWAP_METHOD(swapId, juce::String, getId, setId);
			VS_CREATE_ROUTINE_PARAM_DATA_SWAP_METHOD(swapBoolData, bool, getBoolData, setBoolData);
			VS_CREATE_ROUTINE_PARAM_DATA_SWAP_METHOD(swapChoiceData, int, getChoiceData, setChoiceData);
			VS_CREATE_ROUTINE_PARAM_DATA_SWAP_METHOD(swapFloatData, float, getFloatData, setFloatData);
			VS_CREATE_ROUTINE_PARAM_DATA_SWAP_METHOD(swapIntData, int, getIntData, setIntData);
			VS_CREATE_ROUTINE_PARAM_DATA_SWAP_METHOD(swapControler, juce::String, getControler, setControler);

			VS_CREATE_OBJECT_SELECT_METHOD_BY_ACTION(selectParam, Param, NoteParamAction, VS_NOTEPARAM_SELECT);

			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(IdAction, selectParam, swapId);
			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(BoolDataAction, selectParam, swapBoolData);
			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(ChoiceDataAction, selectParam, swapChoiceData);
			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(FloatDataAction, selectParam, swapFloatData);
			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(IntDataAction, selectParam, swapIntData);
			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(ControlerAction, selectParam, swapControler);
		}
	}
}
