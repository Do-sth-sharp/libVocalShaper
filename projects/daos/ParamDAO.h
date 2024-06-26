#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "../datas/Param.h"

namespace vocalshaper {
	class VSAPI ParamDAO
	{
		ParamDAO() = default;

	public:
		static Param::ParamType getParamType(const Param* ptr);

		static juce::String getId(const Param* ptr);
		static void setId(Param* ptr, juce::String id);

		static bool getBoolData(const Param* ptr);
		static int getChoiceData(const Param* ptr);
		static float getFloatData(const Param* ptr);
		static int getIntData(const Param* ptr);
		static bool setBoolData(Param* ptr, bool value);
		static bool setChoiceData(Param* ptr, int value);
		static bool setFloatData(Param* ptr, float value);
		static bool setIntData(Param* ptr, int value);

		static juce::String getControler(const Param* ptr);
		static void setControler(Param* ptr, juce::String controler);

	public:
		static bool isSaved(const Param* ptr);
		static void save(Param* ptr);
	};
}