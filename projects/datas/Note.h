#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "SerializableProjectStructure.h"
#include "Param.h"
#include "Phoneme.h"

namespace vocalshaper {
	class VSAPI Note : public SerializableProjectStructure
	{
	public:

		enum class NoteType
		{
			MIDI,
			Voice
		}noteType = NoteType::MIDI;									//音符类型

	public:
		Note(NoteType type)
			:SerializableProjectStructure(SerializableProjectStructure::Type::Note),
			noteType(type), phonemes({ new Phoneme })
		{};

	private:
		double st = 0;									//起始位置
		double length = 0;								//长度
		uint8_t pitch = 60;								//音高
		bool tenuto = false;							//延音

		//Voice
		juce::String name = "a";						//歌词
		juce::OwnedArray<Phoneme> phonemes;				//音素
		juce::String flag;								//标志

		//MIDI & Voice
		juce::OwnedArray<Param> params;					//参数

	private:
		friend class NoteDAO;
		friend class ProjectCopier;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Note)
	};
}
