#include "LabelAction.h"
#include "../daos/ProjectDAO.h"
#include "../ProjectProxy.h"

#define VS_CREATE_ROUTINE_LABEL_DATA_SWAP_METHOD(_MethodName, _DataMemType, _DAOGetMethodName, _DAOSetMethodName) \
VS_CREATE_ROUTINE_DATA_SWAP_METHOD(_MethodName, Label, _DataMemType, LabelDAO, _DAOGetMethodName, _DAOSetMethodName)

#define VS_CREATE_ROUTINE_LABEL_DATA_ADD_METHOD(_MethodName, _SubObjectPtrType, _DAOAddMethodName) \
VS_CREATE_ROUTINE_DATA_ADD_METHOD(_MethodName, Label, _SubObjectPtrType, LabelDAO, _DAOAddMethodName)

#define VS_CREATE_ROUTINE_LABEL_DATA_REMOVE_METHOD(_MethodName, _SubObjectPtrType, _DAORemoveMethodName) \
VS_CREATE_ROUTINE_DATA_REMOVE_METHOD(_MethodName, Label, _SubObjectPtrType, LabelDAO, _DAORemoveMethodName)

#define VS_LABEL_SELECT \
ProjectDAO::getLabel(ptr, target->label)

namespace vocalshaper {
	namespace actions {
		namespace label {
			VS_CREATE_ROUTINE_LABEL_DATA_SWAP_METHOD(swapType, vocalshaper::Label::LabelType, getLabelType, setLabelType);
			VS_CREATE_ROUTINE_LABEL_DATA_SWAP_METHOD(swapPosition, vocalshaper::ProjectTime, getPosition, setPosition);
			VS_CREATE_ROUTINE_LABEL_DATA_SWAP_METHOD(swapData, juce::String, getData, setData);

			VS_CREATE_OBJECT_SELECT_METHOD_BY_ACTION(selectLabel, Label, LabelAction, VS_LABEL_SELECT);

			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(TypeAction, selectLabel, swapType);
			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(PositionAction, selectLabel, swapPosition);
			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(DataAction, selectLabel, swapData);
		}
	}
}