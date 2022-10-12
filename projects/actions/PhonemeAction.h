#pragma once
#include "ActionBase.h"

#define VS_CREATE_ROUTINE_PHONEME_ACTION(_ActionName, _DataType, _ActionType) \
VS_CREATE_ROUTINE_ACTION(_ActionName, PhonemeAction, _DataType, _ActionType)

#define VS_CREATE_ROUTINE_PHONEME_ACTION_WITH_INDEXED_OBJECT(_ActionName, _DataMemType, _ActionType) \
VS_CREATE_ROUTINE_ACTION_WITH_INDEXED_OBJECT(_ActionName, PhonemeAction, _DataMemType, _ActionType)

#define VS_PHONEME_TARGET_LIST \
int track = 0; \
int note = 0; \
int phoneme = 0;

#define VS_PHONEME_ACTION_LIST \
Deviation, \
Name, \
IsPre, \
AddPoint, \
RemovePoint

namespace vocalshaper {
	namespace actions {
		VS_CREATE_ROUTINE_ACTION_BASE(PhonemeAction, PhonemeTarget, Phoneme, VS_PHONEME_TARGET_LIST, VS_PHONEME_ACTION_LIST);

		namespace phoneme {
			VS_CREATE_ROUTINE_PHONEME_ACTION(DeviationAction, UInt32Data, Deviation);
			VS_CREATE_ROUTINE_PHONEME_ACTION(NameAction, StringData, Name);
			VS_CREATE_ROUTINE_PHONEME_ACTION(IsPreAction, BoolData, IsPre);

			VS_CREATE_ROUTINE_PHONEME_ACTION_WITH_INDEXED_OBJECT(AddPointAction, vocalshaper::Point*, AddPoint);
			VS_CREATE_ROUTINE_PHONEME_ACTION_WITH_INDEXED_OBJECT(RemovePointAction, std::nullptr_t*, RemovePoint);
		}
	}
}