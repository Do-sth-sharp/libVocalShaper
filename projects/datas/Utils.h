#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>

namespace vocalshaper {
	using ProjectTime = std::pair<uint32_t, uint32_t>;

	ProjectTime VSAPI make_time(uint32_t beatPos, uint32_t deviation);

	double VSAPI timeToDouble(ProjectTime time, uint32_t curveQuantification);
	ProjectTime VSAPI timeFine(ProjectTime time, uint32_t curveQuantification);

	ProjectTime VSAPI getTail(ProjectTime time, uint32_t length, uint32_t curveQuantification);

	bool VSAPI timeEQ(ProjectTime t1, ProjectTime t2, uint32_t curveQuantification);
	bool VSAPI timeNEQ(ProjectTime t1, ProjectTime t2, uint32_t curveQuantification);
	bool VSAPI timeLSS(ProjectTime t1, ProjectTime t2, uint32_t curveQuantification);
	bool VSAPI timeGTR(ProjectTime t1, ProjectTime t2, uint32_t curveQuantification);
	bool VSAPI timeLEQ(ProjectTime t1, ProjectTime t2, uint32_t curveQuantification);
	bool VSAPI timeGEQ(ProjectTime t1, ProjectTime t2, uint32_t curveQuantification);

	ProjectTime VSAPI max(ProjectTime t1, ProjectTime t2, uint32_t curveQuantification);
	ProjectTime VSAPI min(ProjectTime t1, ProjectTime t2, uint32_t curveQuantification);

	//以下实现内联函数

	inline ProjectTime make_time(uint32_t beatPos, uint32_t deviation)
	{
		return std::make_pair(beatPos, deviation);
	}

	inline double timeToDouble(ProjectTime time, uint32_t curveQuantification)
	{
		return time.first + ((double)time.second / curveQuantification);
	}

	inline ProjectTime timeFine(ProjectTime time, uint32_t curveQuantification)
	{
		uint32_t beatFork = std::floor(time.second / (double)curveQuantification);
		time.second -= (beatFork * curveQuantification);
		time.first += beatFork;
		return time;
	}

	inline ProjectTime getTail(ProjectTime time, uint32_t length, uint32_t curveQuantification)
	{
		//防溢出
		uint32_t beatFork = std::floor(length / (double)curveQuantification);
		length -= (beatFork * curveQuantification);
		time.first += beatFork;
		time.second += length;
		return timeFine(time, curveQuantification);
	}

	inline bool timeEQ(ProjectTime t1, ProjectTime t2, uint32_t curveQuantification)
	{
		return timeToDouble(t1, curveQuantification) == timeToDouble(t2, curveQuantification);
	}

	inline bool timeNEQ(ProjectTime t1, ProjectTime t2, uint32_t curveQuantification)
	{
		return !timeEQ(t1, t2, curveQuantification);
	}

	inline bool timeLSS(ProjectTime t1, ProjectTime t2, uint32_t curveQuantification)
	{
		return timeToDouble(t1, curveQuantification) < timeToDouble(t2, curveQuantification);
	}

	inline bool timeGTR(ProjectTime t1, ProjectTime t2, uint32_t curveQuantification)
	{
		return timeToDouble(t1, curveQuantification) > timeToDouble(t2, curveQuantification);
	}

	inline bool timeLEQ(ProjectTime t1, ProjectTime t2, uint32_t curveQuantification)
	{
		return !timeGTR(t1, t2, curveQuantification);
	}

	inline bool timeGEQ(ProjectTime t1, ProjectTime t2, uint32_t curveQuantification)
	{
		return !timeLSS(t1, t2, curveQuantification);
	}

	inline ProjectTime max(ProjectTime t1, ProjectTime t2, uint32_t curveQuantification)
	{
		return timeGTR(t1, t2, curveQuantification) ? t1 : t2;
	}

	inline ProjectTime min(ProjectTime t1, ProjectTime t2, uint32_t curveQuantification)
	{
		return timeLSS(t1, t2, curveQuantification) ? t1 : t2;
	}
}
