#pragma once
#include "../Macros.h"

#include <JuceHeader.h>

namespace vocalshaper {
	enum class VSAPI AdsorbState
	{
		Adsorb1Beat = 1,
		Adsorb1_2Beat = 2,
		Adsorb1_4Beat = 4,
		Adsorb1_6Beat = 6,
		Adsorb1_8Beat = 8,
		Adsorb1_12Beat = 12,
		Adsorb1_16Beat = 16,
		Adsorb1_24Beat = 24,
		Adsorb1_32Beat = 32,
		AdsorbOff = 0
	};

	enum class VSAPI GridState
	{
		Grid1Beat = 1,
		Grid1_2Beat = 2,
		Grid1_4Beat = 4,
		Grid1_6Beat = 6,
		Grid1_8Beat = 8,
		Grid1_12Beat = 12,
		Grid1_16Beat = 16,
		Grid1_24Beat = 24,
		Grid1_32Beat = 32
	};
}