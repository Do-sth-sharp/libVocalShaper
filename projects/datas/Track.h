#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "SerializableProjectStructure.h"
#include "Curve.h"
#include "Note.h"
#include "Plugin.h"
#include "Instr.h"
#include "Wave.h"
#include "Param.h"

namespace vocalshaper {
	class VSAPI Track : public SerializableProjectStructure
	{
	public:
		Track()
			:SerializableProjectStructure(SerializableProjectStructure::Type::Track)
		{};
		~Track() override;

		enum class TrackType {
			Empty,
			Voice,
			Midi,
			Wave
		}trackType = TrackType::Empty;									//轨道类型

	private:
		juce::Colour color = juce::Colour::fromRGB(98, 111, 252);		//轨道颜色
		bool solo = false;												//独奏开关（优先于mute）
		bool mute = false;												//静音开关

		juce::OwnedArray<Curve> curves;									//自动化曲线
		juce::OwnedArray<Plugin> plugins;								//效果器

		//Voice & Midi
		juce::OwnedArray<Note> notes;									//音符

		//Voice
		juce::String singer = "VocalSharp.VocalShaper.KarPlusStrong";	//歌手
		juce::String style;												//音色

		//Midi
		std::unique_ptr<Instr> instrument = nullptr;					//midi乐器

		//Wave
		juce::OwnedArray<Wave> waves;									//音频片段

		//Voice & Wave
		juce::OwnedArray<Param> params;									//轨道参数

	private:
		friend class TrackDAO;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Track)
	};
}
