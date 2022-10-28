#pragma once
#include "ActionBase.h"

#define VS_CREATE_ROUTINE_NOTE_ACTION(_ActionName, _DataType, _ActionType) \
VS_CREATE_ROUTINE_ACTION(_ActionName, NoteAction, _DataType, _ActionType)

#define VS_CREATE_ROUTINE_NOTE_ACTION_WITH_INDEXED_OBJECT(_ActionName, _DataMemType, _ActionType) \
VS_CREATE_ROUTINE_ACTION_WITH_INDEXED_OBJECT(_ActionName, NoteAction, _DataMemType, _ActionType)

#define VS_NOTE_TARGET_LIST \
int track = 0; \
int note = 0;

#define VS_NOTE_ACTION_LIST \
StartTime, \
Length, \
Pitch, \
Tenuto, \
Name, \
Flag, \
AddPhoneme, \
RemovePhoneme, \
AddParam, \
RemoveParam

namespace vocalshaper {
	namespace actions {
		VS_CREATE_ROUTINE_ACTION_BASE(NoteAction, NoteTarget, Note, VS_NOTE_TARGET_LIST, VS_NOTE_ACTION_LIST);

		namespace note {
			VS_CREATE_ROUTINE_NOTE_ACTION(StartTimeAction, DoubleData, StartTime);
			VS_CREATE_ROUTINE_NOTE_ACTION(LengthAction, DoubleData, Length);
			VS_CREATE_ROUTINE_NOTE_ACTION(PitchAction, UInt8Data, Pitch);
			VS_CREATE_ROUTINE_NOTE_ACTION(TenutoAction, BoolData, Tenuto);
			VS_CREATE_ROUTINE_NOTE_ACTION(NameAction, StringData, Name);
			VS_CREATE_ROUTINE_NOTE_ACTION(FlagAction, StringData, Flag);

			VS_CREATE_ROUTINE_NOTE_ACTION_WITH_INDEXED_OBJECT(AddPhonemeAction, vocalshaper::Phoneme*, AddPhoneme);
			VS_CREATE_ROUTINE_NOTE_ACTION_WITH_INDEXED_OBJECT(RemovePhonemeAction, std::nullptr_t*, RemovePhoneme);

			VS_CREATE_ROUTINE_NOTE_ACTION_WITH_INDEXED_OBJECT(AddParamAction, vocalshaper::Param*, AddParam);
			VS_CREATE_ROUTINE_NOTE_ACTION_WITH_INDEXED_OBJECT(RemoveParamAction, std::nullptr_t*, RemoveParam);
		}
	}
}