#include "TrackDAO.h"

namespace vocalshaper {
	Track::TrackType TrackDAO::getTrackType(const Track* ptr)
	{
		if (!ptr) {
			return Track::TrackType::Empty;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->trackType;
	}

	juce::Colour TrackDAO::getColour(const Track* ptr)
	{
		if (!ptr) {
			return juce::Colour();
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->color;
	}

	void TrackDAO::setColour(Track* ptr, juce::Colour color)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->color == color) {
			return;
		}
		ptr->saved = false;
		ptr->color = color;
	}

	bool TrackDAO::getSolo(const Track* ptr)
	{
		if (!ptr) {
			return false;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->solo;
	}

	void TrackDAO::setSolo(Track* ptr, bool solo)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->solo == solo) {
			return;
		}
		ptr->saved = false;
		ptr->solo = solo;
	}

	bool TrackDAO::getMute(const Track* ptr)
	{
		if (!ptr) {
			return false;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->mute;
	}

	void TrackDAO::setMute(Track* ptr, bool mute)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->mute == mute) {
			return;
		}
		ptr->saved = false;
		ptr->mute = mute;
	}

	int TrackDAO::curveSize(const Track* ptr)
	{
		if (!ptr) {
			return -1;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->curves.size();
	}

	Curve* TrackDAO::getCurve(const Track* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->curves[index];
	}

	Curve* TrackDAO::insertCurve(Track* ptr, int index, Curve* curve)
	{
		if (!ptr || !curve) {
			return nullptr;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = false;
		return ptr->curves.insert(index, curve);
	}

	Curve* TrackDAO::releaseCurve(Track* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = false;
		return ptr->curves.removeAndReturn(index);
	}

	int TrackDAO::pluginSize(const Track* ptr)
	{
		if (!ptr) {
			return -1;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->plugins.size();
	}

	Plugin* TrackDAO::getPlugin(const Track* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->plugins[index];
	}

	Plugin* TrackDAO::insertPlugin(Track* ptr, int index, Plugin* plugin)
	{
		if (!ptr || !plugin) {
			return nullptr;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = false;
		return ptr->plugins.insert(index, plugin);
	}

	Plugin* TrackDAO::releasePlugin(Track* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = false;
		return ptr->plugins.removeAndReturn(index);
	}

	int TrackDAO::noteSize(const Track* ptr)
	{
		if (!ptr) {
			return -1;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->notes.size();
	}

	Note* TrackDAO::getNote(const Track* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->notes[index];
	}

	Note* TrackDAO::insertNote(Track* ptr, int index, Note* note)
	{
		if (!ptr || !note) {
			return nullptr;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->trackType == Track::TrackType::Empty) {
			ptr->trackType = Track::TrackType::Voice;
		}
		if (ptr->trackType != Track::TrackType::Voice && ptr->trackType != Track::TrackType::Midi) {
			return nullptr;
		}
		ptr->saved = false;
		return ptr->notes.insert(index, note);
	}

	Note* TrackDAO::releaseNote(Track* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->trackType != Track::TrackType::Voice && ptr->trackType != Track::TrackType::Midi) {
			return nullptr;
		}
		ptr->saved = false;
		auto res = ptr->notes.removeAndReturn(index);
		if (!res) {
			return nullptr;
		}
		if (ptr->trackType == Track::TrackType::Voice && ptr->notes.size() == 0) {
			ptr->trackType = Track::TrackType::Empty;
		}
		if (ptr->trackType == Track::TrackType::Midi && ptr->notes.size() == 0 && !ptr->instrument) {
			ptr->trackType = Track::TrackType::Empty;
		}
		return res;
	}

	juce::String TrackDAO::getSinger(const Track* ptr)
	{
		if (!ptr) {
			return juce::String();
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->singer;
	}

	bool TrackDAO::setSinger(Track* ptr, juce::String singer)
	{
		if (!ptr) {
			return false;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->trackType != Track::TrackType::Voice) {
			return false;
		}
		if (ptr->singer == singer) {
			return true;
		}
		ptr->saved = false;
		ptr->singer = singer;
		return true;
	}

	juce::String TrackDAO::getStyle(const Track* ptr)
	{
		if (!ptr) {
			return juce::String();
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->style;
	}

	bool TrackDAO::setStyle(Track* ptr, juce::String style)
	{
		if (!ptr) {
			return false;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->trackType != Track::TrackType::Voice) {
			return false;
		}
		if (ptr->style == style) {
			return true;
		}
		ptr->saved = false;
		ptr->style = style;
		return true;
	}

	Instr* TrackDAO::getInstrument(const Track* ptr)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->instrument.get();
	}

	Instr* TrackDAO::releaseInstrument(Track* ptr)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->trackType != Track::TrackType::Midi) {
			return nullptr;
		}
		if (!ptr->instrument) {
			return nullptr;
		}
		if (ptr->notes.size() == 0) {
			ptr->trackType = Track::TrackType::Empty;
		}
		ptr->saved = false;
		return ptr->instrument.release();
	}

	bool TrackDAO::setInstrument(Track* ptr, Instr* instr)
	{
		if (!ptr || !instr) {
			return false;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->trackType != Track::TrackType::Empty) {
			ptr->trackType = Track::TrackType::Midi;
		}
		if (ptr->trackType != Track::TrackType::Midi) {
			return false;
		}
		if (ptr->instrument) {
			return false;
		}
		ptr->saved = false;
		ptr->instrument.reset(instr);
		return true;
	}

	int TrackDAO::waveSize(const Track* ptr)
	{
		if (!ptr) {
			return -1;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->waves.size();
	}

	Wave* TrackDAO::getWave(const Track* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->waves[index];
	}

	Wave* TrackDAO::insertWave(Track* ptr, int index, Wave* wave)
	{
		if (!ptr || !wave) {
			return nullptr;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->trackType == Track::TrackType::Empty) {
			ptr->trackType = Track::TrackType::Wave;
		}
		if (ptr->trackType != Track::TrackType::Wave) {
			return nullptr;
		}
		ptr->saved = false;
		return ptr->waves.insert(index, wave);
	}

	Wave* TrackDAO::releaseWave(Track* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->trackType != Track::TrackType::Wave) {
			return nullptr;
		}
		ptr->saved = false;
		auto res = ptr->waves.removeAndReturn(index);
		if (!res) {
			return nullptr;
		}
		if (ptr->notes.size() == 0) {
			ptr->trackType = Track::TrackType::Empty;
		}
		return res;
	}

	int TrackDAO::paramSize(const Track* ptr)
	{
		if (!ptr) {
			return -1;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->params.size();
	}

	Param* TrackDAO::getParam(const Track* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->params[index];
	}

	Param* TrackDAO::insertParam(Track* ptr, int index, Param* param)
	{
		if (!ptr || !param) {
			return nullptr;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->trackType != Track::TrackType::Wave && ptr->trackType != Track::TrackType::Voice) {
			return nullptr;
		}
		ptr->saved = false;
		return ptr->params.insert(index, param);
	}

	Param* TrackDAO::releaseParam(Track* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->trackType != Track::TrackType::Voice && ptr->trackType != Track::TrackType::Wave) {
			return nullptr;
		}
		ptr->saved = false;
		return ptr->params.removeAndReturn(index);
	}

	bool TrackDAO::isSaved(const Track* ptr)
	{
		if (!ptr) {
			return true;
		}
		juce::ScopedReadLock locker(ptr->lock);
		if (!ptr->saved) {
			return false;
		}
		if (ptr->instrument && !InstrDAO::isSaved(ptr->instrument.get())) {
			return false;
		}
		for (auto i : ptr->curves) {
			if (!CurveDAO::isSaved(i)) {
				return false;
			}
		}
		for (auto i : ptr->notes) {
			if (!NoteDAO::isSaved(i)) {
				return false;
			}
		}
		for (auto i : ptr->plugins) {
			if (!PluginDAO::isSaved(i)) {
				return false;
			}
		}
		for (auto i : ptr->waves) {
			if (!WaveDAO::isSaved(i)) {
				return false;
			}
		}
		for (auto i : ptr->params) {
			if (!ParamDAO::isSaved(i)) {
				return false;
			}
		}
		return true;
	}

	void TrackDAO::save(Track* ptr)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = true;
		if (ptr->instrument) {
			InstrDAO::save(ptr->instrument.get());
		}
		for (auto i : ptr->curves) {
			CurveDAO::save(i);
		}
		for (auto i : ptr->notes) {
			NoteDAO::save(i);
		}
		for (auto i : ptr->plugins) {
			PluginDAO::save(i);
		}
		for (auto i : ptr->waves) {
			WaveDAO::save(i);
		}
		for (auto i : ptr->params) {
			ParamDAO::save(i);
		}
	}
}