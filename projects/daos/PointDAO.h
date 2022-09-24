#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "../datas/Point.h"

namespace vocalshaper {
	class VSAPI PointDAO
	{
		PointDAO() = default;

	public:
		static double getX(const Point* ptr);
		static double getY(const Point* ptr);
		static void setX(Point* ptr, double x);
		static void setY(Point* ptr, double y);

	public:
		static bool isSaved(const Point* ptr);
		static void save(Point* ptr);
	};
}