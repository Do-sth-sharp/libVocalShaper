#include "DPointAction.h"
#include "../daos/ProjectDAO.h"
#include "../ProjectProxy.h"

#define VS_CREATE_ROUTINE_DPOINT_DATA_SWAP_METHOD(_MethodName, _DataMemType, _DAOGetMethodName, _DAOSetMethodName) \
VS_CREATE_ROUTINE_DATA_SWAP_METHOD(_MethodName, DPoint, _DataMemType, DPointDAO, _DAOGetMethodName, _DAOSetMethodName)

#define VS_CREATE_ROUTINE_DPOINT_DATA_ADD_METHOD(_MethodName, _SubObjectPtrType, _DAOAddMethodName) \
VS_CREATE_ROUTINE_DATA_ADD_METHOD(_MethodName, DPoint, _SubObjectPtrType, DPointDAO, _DAOAddMethodName)

#define VS_CREATE_ROUTINE_DPOINT_DATA_REMOVE_METHOD(_MethodName, _SubObjectPtrType, _DAORemoveMethodName) \
VS_CREATE_ROUTINE_DATA_REMOVE_METHOD(_MethodName, DPoint, _SubObjectPtrType, DPointDAO, _DAORemoveMethodName)

#define VS_DPOINT_SELECT (target->track == -1) \
? CurveDAO::getPoint(TrackDAO::getCurve(ProjectDAO::getMasterTrack(ptr), target->curve), target->dpoint) \
: CurveDAO::getPoint(TrackDAO::getCurve(ProjectDAO::getTrack(ptr, target->track), target->curve), target->dpoint)

namespace vocalshaper {
	namespace actions {
		namespace dpoint {
			VS_CREATE_ROUTINE_DPOINT_DATA_SWAP_METHOD(swapX, vocalshaper::ProjectTime, getTime, setTime);
			VS_CREATE_ROUTINE_DPOINT_DATA_SWAP_METHOD(swapY, double, getY, setY);
			VS_CREATE_ROUTINE_DPOINT_DATA_SWAP_METHOD(swapDl, double, getDl, setDl);
			VS_CREATE_ROUTINE_DPOINT_DATA_SWAP_METHOD(swapDr, double, getDr, setDr);

			VS_CREATE_OBJECT_SELECT_METHOD_BY_ACTION(selectDPoint, DPoint, DPointAction, VS_DPOINT_SELECT);

			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(XAction, selectDPoint, swapX);
			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(YAction, selectDPoint, swapY);
			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(DlAction, selectDPoint, swapDl);
			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(DrAction, selectDPoint, swapDr);
		}
	}
}