#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "../datas/Curve.h"

namespace vocalshaper {
	class VSAPI CurveDAO
	{
		CurveDAO() = default;

	public:
		static int pointSize(const Curve* ptr);
		static DPoint* getPoint(const Curve* ptr, int index);
		static DPoint* insertPoint(Curve* ptr, int index, DPoint* point);
		static DPoint* releasePoint(Curve* ptr, int index);

	public:
		static bool isSaved(const Curve* ptr);
		static void save(Curve* ptr);

	public:
		static Curve* create();
		static void destory(Curve* ptr);
	};
}