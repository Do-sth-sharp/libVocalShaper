#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "../datas/Label.h"

namespace vocalshaper {
	class VSAPI LabelDAO
	{
		LabelDAO() = default;

	public:
		static Label::LabelType getLabelType(const Label* ptr);
		static void setLabelType(Label* ptr, Label::LabelType type);

		static double getPosition(const Label* ptr);
		static void setPosition(Label* ptr, double time);
		static juce::String getData(const Label* ptr);
		static void setData(Label* ptr, juce::String data);

	public:
		static bool isSaved(const Label* ptr);
		static void save(Label* ptr);
	};
}