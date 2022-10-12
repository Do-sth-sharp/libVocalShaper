#include "ProjectAction.h"
#include "../daos/ProjectDAO.h"
#include "../ProjectProxy.h"

#define VS_CREATE_ROUTINE_PROJECT_DATA_SWAP_METHOD(_MethodName, _DataMemType, _DAOGetMethodName, _DAOSetMethodName) \
VS_CREATE_ROUTINE_DATA_SWAP_METHOD(_MethodName, Project, _DataMemType, ProjectDAO, _DAOGetMethodName, _DAOSetMethodName)

#define VS_CREATE_ROUTINE_PROJECT_DATA_ADD_METHOD(_MethodName, _SubObjectPtrType, _DAOAddMethodName) \
VS_CREATE_ROUTINE_DATA_ADD_METHOD(_MethodName, Project, _SubObjectPtrType, ProjectDAO, _DAOAddMethodName)

#define VS_CREATE_ROUTINE_PROJECT_DATA_REMOVE_METHOD(_MethodName, _SubObjectPtrType, _DAORemoveMethodName) \
VS_CREATE_ROUTINE_DATA_REMOVE_METHOD(_MethodName, Project, _SubObjectPtrType, ProjectDAO, _DAORemoveMethodName)

#define VS_PROJECT_SELECT ptr

namespace vocalshaper {
	namespace actions {
		namespace project {
			VS_CREATE_ROUTINE_PROJECT_DATA_SWAP_METHOD(swapSampleRate, uint32_t, getSampleRate, setSampleRate);
			VS_CREATE_ROUTINE_PROJECT_DATA_SWAP_METHOD(swapBitDeepth, uint32_t, getBitDeepth, setBitDeepth);
			VS_CREATE_ROUTINE_PROJECT_DATA_SWAP_METHOD(swapCurveQuantification, uint32_t, getCurveQuantification, setCurveQuantification);

			VS_CREATE_ROUTINE_PROJECT_DATA_ADD_METHOD(addTrack, Track, insertTrack);
			VS_CREATE_ROUTINE_PROJECT_DATA_REMOVE_METHOD(removeTrack, Track, releaseTrack);

			VS_CREATE_ROUTINE_PROJECT_DATA_ADD_METHOD(addLabel, Label, insertLabel);
			VS_CREATE_ROUTINE_PROJECT_DATA_REMOVE_METHOD(removeLabel, Label, releaseLabel);

			VS_CREATE_ROUTINE_PROJECT_DATA_ADD_METHOD(addScript, Script, insertScript);
			VS_CREATE_ROUTINE_PROJECT_DATA_REMOVE_METHOD(removeScript, Script, releaseScript);

			VS_CREATE_ROUTINE_PROJECT_DATA_ADD_METHOD(addJson, Json, insertAddition);
			VS_CREATE_ROUTINE_PROJECT_DATA_REMOVE_METHOD(removeJson, Json, releaseAddition);

			VS_CREATE_OBJECT_SELECT_METHOD_BY_ACTION(selectProject, Project, ProjectAction, VS_PROJECT_SELECT);

			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(SampleRateAction, selectProject, swapSampleRate);
			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(BitDeepthAction, selectProject, swapBitDeepth);
			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(CurveQuantificationAction, selectProject, swapCurveQuantification);

			VS_CREATE_ADD_ROUTINE_DATA_ACTION_DEFINEITION(AddTrackAction, selectProject, addTrack, removeTrack);
			VS_CREATE_REMOVE_ROUTINE_DATA_ACTION_DEFINEITION(RemoveTrackAction, selectProject, addTrack, removeTrack);

			VS_CREATE_ADD_ROUTINE_DATA_ACTION_DEFINEITION(AddLabelAction, selectProject, addLabel, removeLabel);
			VS_CREATE_REMOVE_ROUTINE_DATA_ACTION_DEFINEITION(RemoveLabelAction, selectProject, addLabel, removeLabel);

			VS_CREATE_ADD_ROUTINE_DATA_ACTION_DEFINEITION(AddScriptAction, selectProject, addScript, removeScript);
			VS_CREATE_REMOVE_ROUTINE_DATA_ACTION_DEFINEITION(RemoveScriptAction, selectProject, addScript, removeScript);

			VS_CREATE_ADD_ROUTINE_DATA_ACTION_DEFINEITION(AddJsonAction, selectProject, addJson, removeJson);
			VS_CREATE_REMOVE_ROUTINE_DATA_ACTION_DEFINEITION(RemoveJsonAction, selectProject, addJson, removeJson);
		}
	}
}
