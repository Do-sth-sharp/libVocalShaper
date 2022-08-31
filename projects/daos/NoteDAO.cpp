#include "NoteDAO.h"

namespace vocalshaper {
	Note::NoteType NoteDAO::getNoteType(const Note* ptr)
	{
		if (!ptr) {
			return Note::NoteType::MIDI;
		}
		return ptr->noteType;
	}

	ProjectTime NoteDAO::getSt(const Note* ptr)
	{
		if (!ptr) {
			return make_time(0, 0);
		}
		return ptr->st;
	}

	void NoteDAO::setSt(Note* ptr, ProjectTime time)
	{
		if (!ptr) {
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
		return ptr->length;
	}

	void NoteDAO::setLength(Note* ptr, uint32_t length)
	{
		if (!ptr) {
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
		return ptr->pitch;
	}

	void NoteDAO::setPitch(Note* ptr, uint8_t pitch)
	{
		if (!ptr) {
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
		return ptr->tenuto;
	}

	void NoteDAO::setTenuto(Note* ptr, bool tenuto)
	{
		if (!ptr) {
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
		return ptr->name;
	}

	bool NoteDAO::setName(Note* ptr, juce::String name)
	{
		if (!ptr) {
			return false;
		}
		if (ptr->noteType != Note::NoteType::Voice) {
			return false;
		}
		ptr->saved = false;
		ptr->name = name;
	}

	int NoteDAO::phonemeSize(const Note* ptr)
	{
		if (!ptr) {
			return -1;
		}
		return ptr->phonemes.size();
	}

	Phoneme* NoteDAO::getPhoneme(const Note* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		return ptr->phonemes[index];
	}

	Phoneme* NoteDAO::insertPhoneme(Note* ptr, int index, Phoneme* phoneme)
	{
		if (!ptr || !phoneme) {
			return nullptr;
		}
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
		return ptr->params.size();
	}

	Param* NoteDAO::getParam(const Note* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		return ptr->params[index];
	}

	Param* NoteDAO::insertParam(Note* ptr, int index, Param* param)
	{
		if (!ptr || !param) {
			return nullptr;
		}
		ptr->saved = false;
		return ptr->params.insert(index, param);
	}

	Param* NoteDAO::releaseParam(Note* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		ptr->saved = false;
		return ptr->params.removeAndReturn(index);
	}

	bool NoteDAO::isSaved(const Note* ptr)
	{
		reutrn true;
	}

	void NoteDAO::save(Note* ptr)
	{

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