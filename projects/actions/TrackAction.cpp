#include "TrackAction.h"
#include "../daos/ProjectDAO.h"
#include "../ProjectProxy.h"

#define VS_CREATE_ROUTINE_TRACK_DATA_SWAP_METHOD(_MethodName, _DataMemType, _DAOGetMethodName, _DAOSetMethodName) \
VS_CREATE_ROUTINE_DATA_SWAP_METHOD(_MethodName, Track, _DataMemType, TrackDAO, _DAOGetMethodName, _DAOSetMethodName)

#define VS_CREATE_ROUTINE_TRACK_DATA_ADD_METHOD(_MethodName, _SubObjectPtrType, _DAOAddMethodName) \
VS_CREATE_ROUTINE_DATA_ADD_METHOD(_MethodName, Track, _SubObjectPtrType, TrackDAO, _DAOAddMethodName)

#define VS_CREATE_ROUTINE_TRACK_DATA_REMOVE_METHOD(_MethodName, _SubObjectPtrType, _DAORemoveMethodName) \
VS_CREATE_ROUTINE_DATA_REMOVE_METHOD(_MethodName, Track, _SubObjectPtrType, TrackDAO, _DAORemoveMethodName)

#define VS_CREATE_ROUTINE_TRACK_SINGLE_DATA_ADD_METHOD(_MethodName, _SubObjectPtrType, _DAOAddMethodName) \
VS_CREATE_ROUTINE_SINGLE_DATA_ADD_METHOD(_MethodName, Track, _SubObjectPtrType, TrackDAO, _DAOAddMethodName)

#define VS_CREATE_ROUTINE_TRACK_SINGLE_DATA_REMOVE_METHOD(_MethodName, _SubObjectPtrType, _DAORemoveMethodName) \
VS_CREATE_ROUTINE_SINGLE_DATA_REMOVE_METHOD(_MethodName, Track, _SubObjectPtrType, TrackDAO, _DAORemoveMethodName)

#define VS_TRACK_SELECT (target->track == -1)\
? ProjectDAO::getMasterTrack(ptr) \
: ProjectDAO::getTrack(ptr, target->track)

namespace vocalshaper {
	namespace actions {
		namespace track {
			VS_CREATE_ROUTINE_TRACK_DATA_SWAP_METHOD(swapName, juce::String, getName, setName);
			VS_CREATE_ROUTINE_TRACK_DATA_SWAP_METHOD(swapColour, juce::Colour, getColour, setColour);
			VS_CREATE_ROUTINE_TRACK_DATA_SWAP_METHOD(swapSolo, bool, getSolo, setSolo);
			VS_CREATE_ROUTINE_TRACK_DATA_SWAP_METHOD(swapMute, bool, getMute, setMute);
			VS_CREATE_ROUTINE_TRACK_DATA_SWAP_METHOD(swapSinger, juce::String, getSinger, setSinger);
			VS_CREATE_ROUTINE_TRACK_DATA_SWAP_METHOD(swapStyle, juce::String, getStyle, setStyle);

			VS_CREATE_ROUTINE_TRACK_SINGLE_DATA_ADD_METHOD(addInstr, Instr, setInstrument);
			VS_CREATE_ROUTINE_TRACK_SINGLE_DATA_REMOVE_METHOD(removeInstr, Instr, releaseInstrument);

			VS_CREATE_ROUTINE_TRACK_DATA_ADD_METHOD(addCurve, Curve, insertCurve);
			VS_CREATE_ROUTINE_TRACK_DATA_REMOVE_METHOD(removeCurve, Curve, releaseCurve);

			VS_CREATE_ROUTINE_TRACK_DATA_ADD_METHOD(addPlugin, Plugin, insertPlugin);
			VS_CREATE_ROUTINE_TRACK_DATA_REMOVE_METHOD(removePlugin, Plugin, releasePlugin);

			VS_CREATE_ROUTINE_TRACK_DATA_ADD_METHOD(addNote, Note, insertNote);
			VS_CREATE_ROUTINE_TRACK_DATA_REMOVE_METHOD(removeNote, Note, releaseNote);

			VS_CREATE_ROUTINE_TRACK_DATA_ADD_METHOD(addWave, Wave, insertWave);
			VS_CREATE_ROUTINE_TRACK_DATA_REMOVE_METHOD(removeWave, Wave, releaseWave);

			VS_CREATE_ROUTINE_TRACK_DATA_ADD_METHOD(addParam, Param, insertParam);
			VS_CREATE_ROUTINE_TRACK_DATA_REMOVE_METHOD(removeParam, Param, releaseParam);

			VS_CREATE_OBJECT_SELECT_METHOD_BY_ACTION(selectTrack, Track, TrackAction, VS_TRACK_SELECT);

			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(NameAction, selectTrack, swapName);
			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(ColourAction, selectTrack, swapColour);
			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(SoloAction, selectTrack, swapSolo);
			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(MuteAction, selectTrack, swapMute);
			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(SingerAction, selectTrack, swapSinger);
			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(StyleAction, selectTrack, swapStyle);

			VS_CREATE_ADD_ROUTINE_SINGLE_DATA_ACTION_DEFINEITION(AddInstrAction, selectTrack, addInstr, removeInstr);
			VS_CREATE_REMOVE_ROUTINE_SINGLE_DATA_ACTION_DEFINEITION(RemoveInstrAction, selectTrack, addInstr, removeInstr);

			VS_CREATE_ADD_ROUTINE_DATA_ACTION_DEFINEITION(AddCurveAction, selectTrack, addCurve, removeCurve);
			VS_CREATE_REMOVE_ROUTINE_DATA_ACTION_DEFINEITION(RemoveCurveAction, selectTrack, addCurve, removeCurve);

			VS_CREATE_ADD_ROUTINE_DATA_ACTION_DEFINEITION(AddPluginAction, selectTrack, addPlugin, removePlugin);
			VS_CREATE_REMOVE_ROUTINE_DATA_ACTION_DEFINEITION(RemovePluginAction, selectTrack, addPlugin, removePlugin);

			VS_CREATE_ADD_ROUTINE_DATA_ACTION_DEFINEITION(AddNoteAction, selectTrack, addNote, removeNote);
			VS_CREATE_REMOVE_ROUTINE_DATA_ACTION_DEFINEITION(RemoveNoteAction, selectTrack, addNote, removeNote);

			VS_CREATE_ADD_ROUTINE_DATA_ACTION_DEFINEITION(AddWaveAction, selectTrack, addWave, removeWave);
			VS_CREATE_REMOVE_ROUTINE_DATA_ACTION_DEFINEITION(RemoveWaveAction, selectTrack, addWave, removeWave);

			VS_CREATE_ADD_ROUTINE_DATA_ACTION_DEFINEITION(AddParamAction, selectTrack, addParam, removeParam);
			VS_CREATE_REMOVE_ROUTINE_DATA_ACTION_DEFINEITION(RemoveParamAction, selectTrack, addParam, removeParam);
		}
	}
}
