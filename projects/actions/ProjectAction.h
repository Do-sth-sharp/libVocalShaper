#pragma once
#include "ActionBase.h"

#define VS_CREATE_ROUTINE_PROJECT_ACTION(_ActionName, _DataType, _ActionType) \
VS_CREATE_ROUTINE_ACTION(_ActionName, ProjectAction, _DataType, _ActionType)

#define VS_CREATE_ROUTINE_PROJECT_ACTION_WITH_INDEXED_OBJECT(_ActionName, _DataMemType, _ActionType) \
VS_CREATE_ROUTINE_ACTION_WITH_INDEXED_OBJECT(_ActionName, ProjectAction, _DataMemType, _ActionType)

#define VS_PROJECT_TARGET_LIST 

#define VS_PROJECT_ACTION_LIST \
SampleRate, \
BitDeepth, \
CurveQuantification, \
AddTrack, \
RemoveTrack, \
AddLabel, \
RemoveLabel, \
AddScript, \
RemoveScript, \
AddJson, \
RemoveJson

namespace vocalshaper {
	namespace actions {
		VS_CREATE_ROUTINE_ACTION_BASE(ProjectAction, ProjectTarget, Project, VS_PROJECT_TARGET_LIST, VS_PROJECT_ACTION_LIST);
		
		namespace project {
			VS_CREATE_ROUTINE_PROJECT_ACTION(SampleRateAction, UInt32Data, SampleRate);
			VS_CREATE_ROUTINE_PROJECT_ACTION(BitDeepthAction, UInt32Data, BitDeepth);
			VS_CREATE_ROUTINE_PROJECT_ACTION(CurveQuantificationAction, UInt32Data, CurveQuantification);

			VS_CREATE_ROUTINE_PROJECT_ACTION_WITH_INDEXED_OBJECT(AddTrackAction, vocalshaper::Track*, AddTrack);
			VS_CREATE_ROUTINE_PROJECT_ACTION_WITH_INDEXED_OBJECT(RemoveTrackAction, std::nullptr_t*, RemoveTrack);

			VS_CREATE_ROUTINE_PROJECT_ACTION_WITH_INDEXED_OBJECT(AddLabelAction, vocalshaper::Label*, AddLabel);
			VS_CREATE_ROUTINE_PROJECT_ACTION_WITH_INDEXED_OBJECT(RemoveLabelAction, std::nullptr_t*, RemoveLabel);

			VS_CREATE_ROUTINE_PROJECT_ACTION_WITH_INDEXED_OBJECT(AddScriptAction, vocalshaper::Script*, AddScript);
			VS_CREATE_ROUTINE_PROJECT_ACTION_WITH_INDEXED_OBJECT(RemoveScriptAction, std::nullptr_t*, RemoveScript);

			VS_CREATE_ROUTINE_PROJECT_ACTION_WITH_INDEXED_OBJECT(AddJsonAction, vocalshaper::Json*, AddJson);
			VS_CREATE_ROUTINE_PROJECT_ACTION_WITH_INDEXED_OBJECT(RemoveJsonAction, std::nullptr_t*, RemoveJson);
		}
	}
}