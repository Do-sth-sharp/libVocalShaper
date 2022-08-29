#include "Utils.h"

namespace vocalshaper {
	ProjectTime make_time(uint32_t beatPos, uint32_t deviation)
	{
		return std::make_pair(beatPos, deviation);
	}
}