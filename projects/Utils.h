#pragma once
#include <JuceHeader.h>

namespace vocalshaper {
	using ProjectTime = std::pair<uint32_t, uint32_t>;

	ProjectTime make_time(uint32_t beatPos, uint32_t deviation)
	{
		return std::make_unique(beatPos, deviation);
	}
}