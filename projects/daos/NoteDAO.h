#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "../datas/Note.h"

namespace vocalshaper {
	class VSAPI NoteDAO
	{
		NoteDAO() = default;

	public:
		static Note::NoteType getNoteType(const Note* ptr);

		static ProjectTime getSt(const Note* ptr);
		static void setSt(Note* ptr, ProjectTime time);
		static uint32_t getLength(const Note* ptr);
		static void setLength(Note* ptr, uint32_t length);
		static uint8_t getPitch(const Note* ptr);
		static void setPitch(Note* ptr, uint8_t pitch);
		static bool getTenuto(const Note* ptr);
		static void setTenuto(Note* ptr, bool tenuto);

		static juce::String getName(const Note* ptr);
		static bool setName(Note* ptr, juce::String name);

		static int phonemeSize(const Note* ptr);
		static Phoneme* getPhoneme(const Note* ptr, int index);
		static Phoneme* insertPhoneme(Note* ptr, int index, Phoneme* phoneme);
		static Phoneme* releasePhoneme(Note* ptr, int index);

		static int paramSize(const Note* ptr);
		static Param* getParam(const Note* ptr, int index);
		static Param* insertParam(Note* ptr, int index, Param* param);
		static Param* releaseParam(Note* ptr, int index);

	public:
		static bool isSaved(const Note* ptr);
		static void save(Note* ptr);

	public:
		static Note* create(Note::NoteType type);
		static void destory(Note* ptr);
	};
}