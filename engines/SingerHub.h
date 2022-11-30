#pragma once
#include "../Macros.h"
#include <JuceHeader.h>
#include "SingerInfo.h"

namespace vocalshaper {
	class VSAPI SingerHub final
	{
	public:
		static bool add(const juce::String& path);
		static void setDefault(const juce::String& id);

		static const SingerInfo getInfoDefault();
		static const SingerInfo getInfo(const juce::String& id);

	private:
		static std::map<juce::String, SingerInfo> list;
		static juce::String defaultID;
		static juce::ReadWriteLock lock;
	};
}