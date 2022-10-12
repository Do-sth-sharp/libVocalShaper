#include "CurveAction.h"
#include "../daos/ProjectDAO.h"
#include "../ProjectProxy.h"

#define VS_CREATE_ROUTINE_CURVE_DATA_SWAP_METHOD(_MethodName, _DataMemType, _DAOGetMethodName, _DAOSetMethodName) \
VS_CREATE_ROUTINE_DATA_SWAP_METHOD(_MethodName, Curve, _DataMemType, CurveDAO, _DAOGetMethodName, _DAOSetMethodName)

#define VS_CREATE_ROUTINE_CURVE_DATA_ADD_METHOD(_MethodName, _SubObjectPtrType, _DAOAddMethodName) \
VS_CREATE_ROUTINE_DATA_ADD_METHOD(_MethodName, Curve, _SubObjectPtrType, CurveDAO, _DAOAddMethodName)

#define VS_CREATE_ROUTINE_CURVE_DATA_REMOVE_METHOD(_MethodName, _SubObjectPtrType, _DAORemoveMethodName) \
VS_CREATE_ROUTINE_DATA_REMOVE_METHOD(_MethodName, Curve, _SubObjectPtrType, CurveDAO, _DAORemoveMethodName)

#define VS_CURVE_SELECT (target->track == -1) \
? TrackDAO::getCurve(ProjectDAO::getMasterTrack(ptr), target->curve) \
: TrackDAO::getCurve(ProjectDAO::getTrack(ptr, target->track), target->curve)

namespace vocalshaper {
	namespace actions {
		namespace curve {
			VS_CREATE_ROUTINE_CURVE_DATA_SWAP_METHOD(swapId, juce::String, getId, setId);

			VS_CREATE_ROUTINE_CURVE_DATA_ADD_METHOD(addDPoint, DPoint, insertPoint);
			VS_CREATE_ROUTINE_CURVE_DATA_REMOVE_METHOD(removeDPoint, DPoint, releasePoint);

			VS_CREATE_OBJECT_SELECT_METHOD_BY_ACTION(selectCurve, Curve, CurveAction, VS_CURVE_SELECT);

			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(IdAction, selectCurve, swapId);

			VS_CREATE_ADD_ROUTINE_DATA_ACTION_DEFINEITION(AddDPointAction, selectCurve, addDPoint, removeDPoint);
			VS_CREATE_REMOVE_ROUTINE_DATA_ACTION_DEFINEITION(RemoveDPointAction, selectCurve, addDPoint, removeDPoint);
		}
	}
}