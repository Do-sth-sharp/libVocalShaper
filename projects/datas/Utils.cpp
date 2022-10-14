#include "Utils.h"

namespace vocalshaper {
	ProjectTime make_time(uint32_t beatPos, uint32_t deviation)
	{
		return std::make_pair(beatPos, deviation);
	}

	double timeToDouble(ProjectTime time, uint32_t curveQuantification)
	{
		return time.first + ((double)time.second / curveQuantification);
	}

	ProjectTime timeFine(ProjectTime time, uint32_t curveQuantification)
	{
		uint32_t beatFork = std::floor(time.second / (double)curveQuantification);
		time.second -= (beatFork * curveQuantification);
		time.first += beatFork;
		return time;
	}

	ProjectTime getTail(ProjectTime time, uint32_t length, uint32_t curveQuantification)
	{
		//防溢出
		uint32_t beatFork = std::floor(length / (double)curveQuantification);
		length -= (beatFork * curveQuantification);
		time.first += beatFork;
		time.second += length;
		return timeFine(time, curveQuantification);
	}

	bool timeEQ(ProjectTime t1, ProjectTime t2, uint32_t curveQuantification)
	{
		return timeToDouble(t1, curveQuantification) == timeToDouble(t2, curveQuantification);
	}

	bool timeNEQ(ProjectTime t1, ProjectTime t2, uint32_t curveQuantification)
	{
		return !timeEQ(t1, t2, curveQuantification);
	}

	bool timeLSS(ProjectTime t1, ProjectTime t2, uint32_t curveQuantification)
	{
		return timeToDouble(t1, curveQuantification) < timeToDouble(t2, curveQuantification);
	}

	bool timeGTR(ProjectTime t1, ProjectTime t2, uint32_t curveQuantification)
	{
		return timeToDouble(t1, curveQuantification) > timeToDouble(t2, curveQuantification);
	}

	bool timeLEQ(ProjectTime t1, ProjectTime t2, uint32_t curveQuantification)
	{
		return !timeGTR(t1, t2, curveQuantification);
	}

	bool timeGEQ(ProjectTime t1, ProjectTime t2, uint32_t curveQuantification)
	{
		return !timeLSS(t1, t2, curveQuantification);
	}

	ProjectTime max(ProjectTime t1, ProjectTime t2, uint32_t curveQuantification)
	{
		return timeGTR(t1, t2, curveQuantification) ? t1 : t2;
	}

	ProjectTime min(ProjectTime t1, ProjectTime t2, uint32_t curveQuantification)
	{
		return timeLSS(t1, t2, curveQuantification) ? t1 : t2;
	}
}