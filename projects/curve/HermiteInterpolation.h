#pragma once
#include "../../Macros.h"
#include <JuceHeader.h>
#include "../datas/Curve.h"

namespace vocalshaper {
	class VSAPI HermiteInterpolation final
	{
	public:
		//区间缓存
		struct HermiteTemp final
		{
			double x0 = 0, x1 = 0;
			double y0 = 0, y1 = 0;
			double d0 = 0, d1 = 0;
		};

		//获取当前时间所在区间索引
		static int selectPoint(double x, const Curve* curve);

		//根据索引构建运算缓存
		static const HermiteTemp selectTemp(int index, const Curve* curve, double valueDefault);

		//根据当前时间构建运算缓存
		static const HermiteTemp selectTemp(double x, const Curve* curve, double valueDefault);

		//根据缓存计算值
		static double getY(double x, const HermiteTemp temp);

		//根据缓存计算导数
		static double getD(double x, const HermiteTemp temp);

		//根据当前时间计算值
		static double getY(double x, const Curve* curve, double valueDefault);

		//根据当前时间计算导数
		static double getD(double x, const Curve* curve, double valueDefault);

	private:
		enum class CompareResult {
			EQ,
			GTR,
			LSS
		};
		template<typename Func>
		static int search(int low, int high, Func func);

		static inline double getY(double x, double x0, double x1, double y0, double y1, double d0, double d1);
		static inline double getD(double x, double x0, double x1, double y0, double y1, double d0, double d1);

		static inline double getDeltaX0(double x, double x0);
		static inline double getDeltaX1(double x, double x1);
		static inline double getDeltaX(double x0, double x1);

		static inline double getT0(double x, double x0, double x1);
		static inline double getT1(double x, double x0, double x1);

		static inline double getK0(double x, double x0, double x1);
		static inline double getK1(double x, double x0, double x1);

		static inline double getL0(double x, double x0, double x1);
		static inline double getL1(double x, double x0, double x1);

		static inline double getDT0(double x0, double x1);
		static inline double getDT1(double x0, double x1);

		static inline double getDK0(double x, double x0, double x1);
		static inline double getDK1(double x, double x0, double x1);

		static inline double getDL0(double x, double x0, double x1);
		static inline double getDL1(double x, double x0, double x1);
	};
}