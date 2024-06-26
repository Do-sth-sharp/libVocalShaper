﻿#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "SerializableProjectStructure.h"
#include "Track.h"
#include "Label.h"
#include "Script.h"
#include "Json.h"

namespace vocalshaper {
	class VSAPI Project : public SerializableProjectStructure
	{
	public:
		Project()
			:SerializableProjectStructure(SerializableProjectStructure::Type::Project),
			masterTrack(new Track)
		{};

	private:
		juce::OwnedArray<Track> tracks;									//轨道
		juce::OwnedArray<Label> labels;									//标签

		uint32_t sampleRate = 48000;									//采样率
		uint32_t bitDeepth = 16;										//位深度
		uint32_t curveQuantification = 480;								//参数曲线量化（时间偏移最小量化，点每拍）

		std::unique_ptr<Track> masterTrack = nullptr;					//主轨道

		juce::OwnedArray<Script> scripts;								//脚本
		juce::OwnedArray<Json> additions;								//附加属性

	private:
		friend class ProjectDAO;
		friend class ProjectCopier;
		friend class EventUndo;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Project)
	};
}
