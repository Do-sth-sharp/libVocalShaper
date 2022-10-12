#include "PointAction.h"
#include "../daos/ProjectDAO.h"
#include "../ProjectProxy.h"

#define VS_CREATE_ROUTINE_POINT_DATA_SWAP_METHOD(_MethodName, _DataMemType, _DAOGetMethodName, _DAOSetMethodName) \
VS_CREATE_ROUTINE_DATA_SWAP_METHOD(_MethodName, Point, _DataMemType, PointDAO, _DAOGetMethodName, _DAOSetMethodName)

#define VS_CREATE_ROUTINE_POINT_DATA_ADD_METHOD(_MethodName, _SubObjectPtrType, _DAOAddMethodName) \
VS_CREATE_ROUTINE_DATA_ADD_METHOD(_MethodName, Point, _SubObjectPtrType, PointDAO, _DAOAddMethodName)

#define VS_CREATE_ROUTINE_POINT_DATA_REMOVE_METHOD(_MethodName, _SubObjectPtrType, _DAORemoveMethodName) \
VS_CREATE_ROUTINE_DATA_REMOVE_METHOD(_MethodName, Point, _SubObjectPtrType, PointDAO, _DAORemoveMethodName)

#define VS_POINT_SELECT \
PhonemeDAO::getTimePoint(NoteDAO::getPhoneme(TrackDAO::getNote(ProjectDAO::getTrack(ptr, target->track), target->note), target->phoneme), target->point)

namespace vocalshaper {
	namespace actions {
		namespace point {
			VS_CREATE_ROUTINE_POINT_DATA_SWAP_METHOD(swapX, double, getX, setX);
			VS_CREATE_ROUTINE_POINT_DATA_SWAP_METHOD(swapY, double, getY, setY);

			VS_CREATE_OBJECT_SELECT_METHOD_BY_ACTION(selectPoint, Point, PointAction, VS_POINT_SELECT);

			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(XAction, selectPoint, swapX);
			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(YAction, selectPoint, swapY);
		}
	}
}