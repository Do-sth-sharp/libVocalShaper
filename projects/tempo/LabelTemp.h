﻿#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>

namespace vocalshaper {
	class VSAPI ProjectProxy;
	class VSAPI Label;
	class VSAPI LabelTemp final
	{
	public:
		explicit LabelTemp(ProjectProxy* parent);
		~LabelTemp() = default;

		struct LabelData final {
			double x = 0.0;			//位置
			double tempo = 120.0;		//曲速
			uint8_t beat = 4;		//拍号
			bool autoTempo = false;	//曲速自动插值
		};

		//从data数据刷新缓存
		void refresh();

	private:
		juce::Array<LabelData> list;
		juce::ReadWriteLock lock;

		ProjectProxy* parent = nullptr;

		bool parseLabel(const Label* label, LabelData& result, uint32_t curveQ, double& tempoTemp, uint8_t& beatTemp);
		bool parseLuaLabel(const juce::String& data, LabelData& result, double& tempoTemp, uint8_t& beatTemp);
		bool parseIniLabel(const juce::String& data, LabelData& result, double& tempoTemp, uint8_t& beatTemp);
		bool parseXmlLabel(const juce::String& data, LabelData& result, double& tempoTemp, uint8_t& beatTemp);
		bool parseJsonLabel(const juce::String& data, LabelData& result, double& tempoTemp, uint8_t& beatTemp);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LabelTemp)
	};
}