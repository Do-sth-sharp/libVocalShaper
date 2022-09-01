#include "NoteDAO.h"

namespace vocalshaper {
	Note::NoteType NoteDAO::getNoteType(const Note* ptr)
	{
		if (!ptr) {
			return Note::NoteType::MIDI;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->noteType;
	}

	ProjectTime NoteDAO::getSt(const Note* ptr)
	{
		if (!ptr) {
			return make_time(0, 0);
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->st;
	}

	void NoteDAO::setSt(Note* ptr, ProjectTime time)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->st == time) {
			return;
		}
		ptr->saved = false;
		ptr->st = time;
	}

	uint32_t NoteDAO::getLength(const Note* ptr)
	{
		if (!ptr) {
			return 0;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->length;
	}

	void NoteDAO::setLength(Note* ptr, uint32_t length)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->length == length) {
			return;
		}
		ptr->saved = false;
		ptr->length = length;
	}

	uint8_t NoteDAO::getPitch(const Note* ptr)
	{
		if (!ptr) {
			return 0;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->pitch;
	}

	void NoteDAO::setPitch(Note* ptr, uint8_t pitch)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->pitch == pitch) {
			return;
		}
		ptr->saved = false;
		ptr->pitch = pitch;
	}

	bool NoteDAO::getTenuto(const Note* ptr)
	{
		if (!ptr) {
			return false;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->tenuto;
	}

	void NoteDAO::setTenuto(Note* ptr, bool tenuto)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->tenuto == tenuto) {
			return;
		}
		ptr->saved = false;
		ptr->tenuto = tenuto;
	}

	juce::String NoteDAO::getName(const Note* ptr)
	{
		if (!ptr) {
			return juce::String();
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->name;
	}

	bool NoteDAO::setName(Note* ptr, juce::String name)
	{
		if (!ptr) {
			return false;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->noteType != Note::NoteType::Voice) {
			return false;
		}
		if (ptr->name == name) {
			return true;
		}
		ptr->saved = false;
		ptr->name = name;
		return true;
	}

	int NoteDAO::phonemeSize(const Note* ptr)
	{
		if (!ptr) {
			return -1;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->phonemes.size();
	}

	Phoneme* NoteDAO::getPhoneme(const Note* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->phonemes[index];
	}

	Phoneme* NoteDAO::insertPhoneme(Note* ptr, int index, Phoneme* phoneme)
	{
		if (!ptr || !phoneme) {
			return nullptr;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->noteType != Note::NoteType::Voice) {
			return nullptr;
		}
		ptr->saved = false;
		return ptr->phonemes.insert(index, phoneme);
	}

	Phoneme* NoteDAO::releasePhoneme(Note* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->noteType != Note::NoteType::Voice) {
			return nullptr;
		}
		ptr->saved = false;
		return ptr->phonemes.removeAndReturn(index);
	}

	int NoteDAO::paramSize(const Note* ptr)
	{
		if (!ptr) {
			return -1;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->params.size();
	}

	Param* NoteDAO::getParam(const Note* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->params[index];
	}

	Param* NoteDAO::insertParam(Note* ptr, int index, Param* param)
	{
		if (!ptr || !param) {
			return nullptr;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = false;
		return ptr->params.insert(index, param);
	}

	Param* NoteDAO::releaseParam(Note* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = false;
		return ptr->params.removeAndReturn(index);
	}

	bool NoteDAO::isSaved(const Note* ptr)
	{
		if (!ptr) {
			return true;
		}
		juce::ScopedReadLock locker(ptr->lock);
		if (!ptr->saved) {
			return false;
		}
		for (auto i : ptr->params) {
			if (!ParamDAO::isSaved(i)) {
				return false;
			}
		}
		for (auto i : ptr->phonemes) {
			if (!PhonemeDAO::isSaved(i)) {
				return false;
			}
		}
		return true;
	}

	void NoteDAO::save(Note* ptr)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = true;
		for (auto i : ptr->params) {
			ParamDAO::save(i);
		}
		for (auto i : ptr->phonemes) {
			PhonemeDAO::save(i);
		}
	}

	Note* NoteDAO::create(Note::NoteType type)
	{
		auto ptr = new Note;
		ptr->noteType = type;
		return ptr;
	}

	void NoteDAO::destory(Note* ptr)
	{
		delete ptr;
	}
}