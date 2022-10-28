#include "WaveAction.h"
#include "../daos/ProjectDAO.h"
#include "../ProjectProxy.h"

#define VS_CREATE_ROUTINE_WAVE_DATA_SWAP_METHOD(_MethodName, _DataMemType, _DAOGetMethodName, _DAOSetMethodName) \
VS_CREATE_ROUTINE_DATA_SWAP_METHOD(_MethodName, Wave, _DataMemType, WaveDAO, _DAOGetMethodName, _DAOSetMethodName)

#define VS_CREATE_ROUTINE_WAVE_DATA_ADD_METHOD(_MethodName, _SubObjectPtrType, _DAOAddMethodName) \
VS_CREATE_ROUTINE_DATA_ADD_METHOD(_MethodName, Wave, _SubObjectPtrType, WaveDAO, _DAOAddMethodName)

#define VS_CREATE_ROUTINE_WAVE_DATA_REMOVE_METHOD(_MethodName, _SubObjectPtrType, _DAORemoveMethodName) \
VS_CREATE_ROUTINE_DATA_REMOVE_METHOD(_MethodName, Wave, _SubObjectPtrType, WaveDAO, _DAORemoveMethodName)

#define VS_WAVE_SELECT \
TrackDAO::getWave(ProjectDAO::getTrack(ptr, target->track), target->wave)

namespace vocalshaper {
	namespace actions {
		namespace wave {
			VS_CREATE_ROUTINE_WAVE_DATA_SWAP_METHOD(swapSource, juce::String, getSource, setSource);
			VS_CREATE_ROUTINE_WAVE_DATA_SWAP_METHOD(swapDeviation, double, getDeviation, setDeviation);
			VS_CREATE_ROUTINE_WAVE_DATA_SWAP_METHOD(swapStartTime, double, getSt, setSt);
			VS_CREATE_ROUTINE_WAVE_DATA_SWAP_METHOD(swapLength, double, getLength, setLength);

			VS_CREATE_OBJECT_SELECT_METHOD_BY_ACTION(selectWave, Wave, WaveAction, VS_WAVE_SELECT);

			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(SourceAction, selectWave, swapSource);
			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(DeviationAction, selectWave, swapDeviation);
			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(StartTimeAction, selectWave, swapStartTime);
			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(LengthAction, selectWave, swapLength);
		}
	}
}
