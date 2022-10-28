#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "../datas/DPoint.h"

namespace vocalshaper {
	class VSAPI DPointDAO
	{
		DPointDAO() = default;

	public:
		static double getTime(const DPoint* ptr);
		static void setTime(DPoint* ptr, double time);
		static double getY(const DPoint* ptr);
		static void setY(DPoint* ptr, double y);
		static double getDl(const DPoint* ptr);
		static void setDl(DPoint* ptr, double dl);
		static double getDr(const DPoint* ptr);
		static void setDr(DPoint* ptr, double dr);

	public:
		static bool isSaved(const DPoint* ptr);
		static void save(DPoint* ptr);
	};
}