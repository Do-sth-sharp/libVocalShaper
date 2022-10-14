#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>

namespace vocalshaper {
	using ProjectTime = std::pair<uint32_t, uint32_t>;

	inline ProjectTime VSAPI make_time(uint32_t beatPos, uint32_t deviation);

	inline double VSAPI timeToDouble(ProjectTime time, uint32_t curveQuantification);
	inline ProjectTime VSAPI timeFine(ProjectTime time, uint32_t curveQuantification);

	inline ProjectTime VSAPI getTail(ProjectTime time, uint32_t length, uint32_t curveQuantification);

	inline bool VSAPI timeEQ(ProjectTime t1, ProjectTime t2, uint32_t curveQuantification);
	inline bool VSAPI timeNEQ(ProjectTime t1, ProjectTime t2, uint32_t curveQuantification);
	inline bool VSAPI timeLSS(ProjectTime t1, ProjectTime t2, uint32_t curveQuantification);
	inline bool VSAPI timeGTR(ProjectTime t1, ProjectTime t2, uint32_t curveQuantification);
	inline bool VSAPI timeLEQ(ProjectTime t1, ProjectTime t2, uint32_t curveQuantification);
	inline bool VSAPI timeGEQ(ProjectTime t1, ProjectTime t2, uint32_t curveQuantification);

	inline ProjectTime VSAPI max(ProjectTime t1, ProjectTime t2, uint32_t curveQuantification);
	inline ProjectTime VSAPI min(ProjectTime t1, ProjectTime t2, uint32_t curveQuantification);
}
