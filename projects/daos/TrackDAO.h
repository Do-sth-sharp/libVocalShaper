#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "../datas/Track.h"

namespace vocalshaper {
	class VSAPI TrackDAO
	{
		TrackDAO() = default;

	public:
		static Track::TrackType getTrackType(const Track* ptr);

		static juce::Colour getColour(const Track* ptr);
		static void setColour(Track* ptr, juce::Colour color);
		static bool getSolo(const Track* ptr);
		static void setSolo(Track* ptr, bool solo);
		static bool getMute(const Track* ptr);
		static void setMute(Track* ptr, bool mute);

		static int curveSize(const Track* ptr);
		static Curve* getCurve(const Track* ptr, int index);
		static Curve* insertCurve(Track* ptr, int index, Curve* curve);
		static Curve* releaseCurve(Track* ptr, int index);

		static int pluginSize(const Track* ptr);
		static Plugin* getPlugin(const Track* ptr, int index);
		static Plugin* insertPlugin(Track* ptr, int index, Plugin* plugin);
		static Plugin* releasePlugin(Track* ptr, int index);

		static int noteSize(const Track* ptr);
		static Note* getNote(const Track* ptr, int index);
		static Note* insertNote(Track* ptr, int index, Note* note);
		static Note* releaseNote(Track* ptr, int index);

		static juce::String getSinger(const Track* ptr);
		static bool setSinger(Track* ptr, juce::String singer);
		static juce::String getStyle(const Track* ptr);
		static bool setStyle(Track* ptr, juce::String style);

		static Instr* getInstrument(const Track* ptr);
		static Instr* releaseInstrument(Track* ptr);
		static bool setInstrument(Track* ptr, Instr* instr);

		static int waveSize(const Track* ptr);
		static Wave* getWave(const Track* ptr, int index);
		static Wave* insertWave(Track* ptr, int index, Wave* wave);
		static Wave* releaseWave(Track* ptr, int index);

		static int paramSize(const Track* ptr);
		static Param* getParam(const Track* ptr, int index);
		static Param* insertParam(Track* ptr, int index, Param* param);
		static Param* releaseParam(Track* ptr, int index);

	public:
		static bool isSaved(const Track* ptr);
		static void save(Track* ptr);

	public:
		static Track* create();
		static void destory(Track* ptr);
	};
}