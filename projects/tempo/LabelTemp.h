#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "../datas/Label.h"

extern "C" {
	struct VSAPI lua_State;
}

namespace vocalshaper {
	class VSAPI ProjectProxy;

	class VSAPI LabelTemp final
	{
	public:
		explicit LabelTemp(ProjectProxy* parent);
		~LabelTemp() = default;

		struct LabelData final {
			double x = 0.0;			//位置
			double tempo = 120.0;	//曲速
			uint8_t beat = 4;		//拍号
			bool autoTempo = false;	//曲速自动插值
		};

		enum class ParseResult {
			OK,		//成功
			TLE,	//超时
			SE,		//语法错误
			TE,		//类型错误
			ME,		//内存错误
			VME		//虚拟机错误
		};

		//从data数据刷新缓存
		void refresh();

		ParseResult parseNow(const juce::String& data, LabelData& result, Label::LabelType type, double x, double tempoTemp, uint8_t beatTemp) const;

	private:
		friend class TempoTemp;
		friend class BeatTemp;

		std::unique_ptr<lua_State, std::function<void(lua_State*)>> luaState;
		juce::Array<LabelData> list;
		juce::ReadWriteLock lock;

		ProjectProxy* parent = nullptr;

		ParseResult parseLabel(const Label* label, LabelData& result, double& tempoTemp, uint8_t& beatTemp) const;
		ParseResult parseLuaLabel(const juce::String& data, LabelData& result, double x, double& tempoTemp, uint8_t& beatTemp) const;
		ParseResult parseIniLabel(const juce::String& data, LabelData& result, double x, double& tempoTemp, uint8_t& beatTemp) const;
		ParseResult parseXmlLabel(const juce::String& data, LabelData& result, double x, double& tempoTemp, uint8_t& beatTemp) const;
		ParseResult parseJsonLabel(const juce::String& data, LabelData& result, double x, double& tempoTemp, uint8_t& beatTemp) const;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LabelTemp)
	};
}