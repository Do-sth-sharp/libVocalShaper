#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "SerializableProjectStructure.h"
#include "Utils.h"
#include "Param.h"
#include "Phoneme.h"

namespace vocalshaper {
	class VSAPI Note : public SerializableProjectStructure
	{
	public:
		Note()
			:SerializableProjectStructure(SerializableProjectStructure::Type::Note)
		{};
		~Note() override;

		enum class NoteType
		{
			MIDI,
			Voice
		}noteType = NoteType::MIDI;									//音符类型

	private:
		ProjectTime st = make_time(0, 0);							//起始位置
		uint32_t length = 0;										//长度
		uint8_t pitch = 60;											//音高
		bool tenuto = false;										//延音

		//Voice
		juce::String name = "a";									//歌词
		juce::OwnedArray<Phoneme> phonemes;							//音素

		//MIDI & Voice
		juce::OwnedArray<Param> params;								//参数

	private:
		friend class NoteDAO;
		friend class ProjectCopier;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Note)
	};
}
