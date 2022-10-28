#pragma once
#include "ActionBase.h"

#define VS_CREATE_ROUTINE_WAVE_ACTION(_ActionName, _DataType, _ActionType) \
VS_CREATE_ROUTINE_ACTION(_ActionName, WaveAction, _DataType, _ActionType)

#define VS_CREATE_ROUTINE_WAVE_ACTION_WITH_INDEXED_OBJECT(_ActionName, _DataMemType, _ActionType) \
VS_CREATE_ROUTINE_ACTION_WITH_INDEXED_OBJECT(_ActionName, WaveAction, _DataMemType, _ActionType)

#define VS_WAVE_TARGET_LIST \
int track = 0; \
int wave = 0;

#define VS_WAVE_ACTION_LIST \
Source, \
Deviation, \
StartTime, \
Length

namespace vocalshaper {
	namespace actions {
		VS_CREATE_ROUTINE_ACTION_BASE(WaveAction, WaveTarget, Wave, VS_WAVE_TARGET_LIST, VS_WAVE_ACTION_LIST);

		namespace wave {
			VS_CREATE_ROUTINE_WAVE_ACTION(SourceAction, StringData, Source);
			VS_CREATE_ROUTINE_WAVE_ACTION(DeviationAction, DoubleData, Deviation);
			VS_CREATE_ROUTINE_WAVE_ACTION(StartTimeAction, DoubleData, StartTime);
			VS_CREATE_ROUTINE_WAVE_ACTION(LengthAction, DoubleData, Length);
		}
	}
}