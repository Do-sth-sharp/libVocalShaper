#pragma once
#include "../Macros.h"
#include <JuceHeader.h>
#include "ParamInfo.h"

namespace vocalshaper {
	class Curve;
	class Track;
	class Note;
	class Param;

	//引擎辅助类
	class VSAPI EngineHelper final
	{
	public:
		static const Curve* findCurve(const Track* track, const juce::String& id);
		static const Param* findParam(const Track* track, const juce::String& id);
		static const Param* findParam(const Note* note, const juce::String& id);

		static const juce::String makeFullID(const juce::String& shortID);

		static const ParamInfo findParamInfo(
			const ParamInfoList& list, const juce::String& shortID);
	};
}