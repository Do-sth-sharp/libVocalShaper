#pragma once
#include "ActionBase.h"

#define VS_CREATE_ROUTINE_TRACK_ACTION(_ActionName, _DataType, _ActionType) \
VS_CREATE_ROUTINE_ACTION(_ActionName, TrackAction, _DataType, _ActionType)

#define VS_CREATE_ROUTINE_TRACK_ACTION_WITH_INDEXED_OBJECT(_ActionName, _DataMemType, _ActionType) \
VS_CREATE_ROUTINE_ACTION_WITH_INDEXED_OBJECT(_ActionName, TrackAction, _DataMemType, _ActionType)

#define VS_CREATE_ROUTINE_TRACK_ACTION_WITH_SINGLE_OBJECT(_ActionName, _DataMemType, _ActionType) \
VS_CREATE_ROUTINE_ACTION_WITH_SINGLE_OBJECT(_ActionName, TrackAction, _DataMemType, _ActionType)

#define VS_TRACK_TARGET_LIST \
int track = 0;

#define VS_TRACK_ACTION_LIST \
Name, \
Colour, \
Solo, \
Mute, \
Singer, \
Style, \
AddInstr, \
RemoveInstr, \
AddCurve, \
RemoveCurve, \
AddPlugin, \
RemovePlugin, \
AddNote, \
RemoveNote, \
AddWave, \
RemoveWave, \
AddParam, \
RemoveParam

namespace vocalshaper {
	namespace actions {
		VS_CREATE_ROUTINE_ACTION_BASE(TrackAction, TrackTarget, Track, VS_TRACK_TARGET_LIST, VS_TRACK_ACTION_LIST);

		namespace track {
			VS_CREATE_ROUTINE_TRACK_ACTION(NameAction, StringData, Name);
			VS_CREATE_ROUTINE_TRACK_ACTION(ColourAction, ColorData, Colour);
			VS_CREATE_ROUTINE_TRACK_ACTION(SoloAction, BoolData, Solo);
			VS_CREATE_ROUTINE_TRACK_ACTION(MuteAction, BoolData, Mute);
			VS_CREATE_ROUTINE_TRACK_ACTION(SingerAction, StringData, Singer);
			VS_CREATE_ROUTINE_TRACK_ACTION(StyleAction, StringData, Style);

			VS_CREATE_ROUTINE_TRACK_ACTION_WITH_SINGLE_OBJECT(AddInstrAction, vocalshaper::Instr*, AddInstr);
			VS_CREATE_ROUTINE_TRACK_ACTION_WITH_SINGLE_OBJECT(RemoveInstrAction, std::nullptr_t, RemoveInstr);

			VS_CREATE_ROUTINE_TRACK_ACTION_WITH_INDEXED_OBJECT(AddCurveAction, vocalshaper::Curve*, AddCurve);
			VS_CREATE_ROUTINE_TRACK_ACTION_WITH_INDEXED_OBJECT(RemoveCurveAction, std::nullptr_t, RemoveCurve);

			VS_CREATE_ROUTINE_TRACK_ACTION_WITH_INDEXED_OBJECT(AddPluginAction, vocalshaper::Plugin*, AddPlugin);
			VS_CREATE_ROUTINE_TRACK_ACTION_WITH_INDEXED_OBJECT(RemovePluginAction, std::nullptr_t, RemovePlugin);

			VS_CREATE_ROUTINE_TRACK_ACTION_WITH_INDEXED_OBJECT(AddNoteAction, vocalshaper::Note*, AddNote);
			VS_CREATE_ROUTINE_TRACK_ACTION_WITH_INDEXED_OBJECT(RemoveNoteAction, std::nullptr_t, RemoveNote);

			VS_CREATE_ROUTINE_TRACK_ACTION_WITH_INDEXED_OBJECT(AddWaveAction, vocalshaper::Wave*, AddWave);
			VS_CREATE_ROUTINE_TRACK_ACTION_WITH_INDEXED_OBJECT(RemoveWaveAction, std::nullptr_t, RemoveWave);

			VS_CREATE_ROUTINE_TRACK_ACTION_WITH_INDEXED_OBJECT(AddParamAction, vocalshaper::Param*, AddParam);
			VS_CREATE_ROUTINE_TRACK_ACTION_WITH_INDEXED_OBJECT(RemoveParamAction, std::nullptr_t, RemoveParam);
		}
	}
}