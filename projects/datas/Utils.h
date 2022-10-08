#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>

namespace vocalshaper {
	using ProjectTime = std::pair<uint32_t, uint32_t>;

	ProjectTime VSAPI make_time(uint32_t beatPos, uint32_t deviation);
	double VSAPI timeToDouble(ProjectTime time, uint32_t curveQuantification);
}