#include "HermiteInterpolation.h"
#include "../daos/CurveDAO.h"

namespace vocalshaper {
	int HermiteInterpolation::selectPoint(double x, const Curve* curve)
	{
		if (!curve) {
			return -1;
		}

		//如果没有控制点
		int pointSize = vocalshaper::CurveDAO::pointSize(curve);
		if (pointSize == 0) {
			return 0;
		}

		//比较函数
		auto CFunc = [curve, pointSize, x](int index)->CompareResult {
			bool hasLast = index > 0;
			bool hasNext = index < pointSize;
			if ((hasLast ? (x >= vocalshaper::DPointDAO::getTime(vocalshaper::CurveDAO::getPoint(curve, index - 1))) : true) &&
				(hasNext ? (x < vocalshaper::DPointDAO::getTime(vocalshaper::CurveDAO::getPoint(curve, index))) : true)) {
				return CompareResult::EQ;
			}
			else if (hasNext ? (x >= vocalshaper::DPointDAO::getTime(vocalshaper::CurveDAO::getPoint(curve, index))) : false) {
				return CompareResult::GTR;
			}
			else {
				return CompareResult::LSS;
			}
		};

		//利用顺序缓存加速查找
		static int lastIndexTemp = -1;
		if (lastIndexTemp >= 0 && lastIndexTemp <= pointSize) {
			//如果缓存命中
			if (CFunc(lastIndexTemp) == CompareResult::EQ) {
				return lastIndexTemp;
			}

			//如果下一缓存命中
			if (lastIndexTemp < pointSize) {
				if (CFunc(lastIndexTemp + 1) == CompareResult::EQ) {
					return ++lastIndexTemp;
				}
			}
		}

		//在首点前
		if (CFunc(0) == CompareResult::EQ) {
			return lastIndexTemp = 0;
		}

		//在末点后
		if (CFunc(pointSize) == CompareResult::EQ) {
			return lastIndexTemp = pointSize;
		}

		//二分查找
		return lastIndexTemp = HermiteInterpolation::search(0, pointSize, CFunc);
	}

	const HermiteInterpolation::HermiteTemp HermiteInterpolation::selectTemp(
		int index, const Curve* curve, double valueDefault)
	{
		double x0 = 0, x1 = DBL_MAX;
		double y0 = valueDefault, y1 = valueDefault;
		double d0 = 0, d1 = 0;

		int pointSize = vocalshaper::CurveDAO::pointSize(curve);

		//如果有前点
		if (index > 0) {
			auto lastPoint = vocalshaper::CurveDAO::getPoint(curve, index - 1);
			if (lastPoint) {
				x0 = vocalshaper::DPointDAO::getTime(lastPoint);
				y0 = vocalshaper::DPointDAO::getY(lastPoint);
				d0 = vocalshaper::DPointDAO::getDr(lastPoint);
			}
		}

		//如果有后点
		if (index < pointSize) {
			auto nextPoint = vocalshaper::CurveDAO::getPoint(curve, index);
			if (nextPoint) {
				x1 = vocalshaper::DPointDAO::getTime(nextPoint);
				y1 = vocalshaper::DPointDAO::getY(nextPoint);
				d1 = vocalshaper::DPointDAO::getDl(nextPoint);
			}
		}

		return HermiteInterpolation::HermiteTemp{
			.x0 = x0,
			.x1 = x1,
			.y0 = y0,
			.y1 = y1,
			.d0 = d0,
			.d1 = d1
		};
	}

	const HermiteInterpolation::HermiteTemp HermiteInterpolation::selectTemp(
		double x, const Curve* curve, double valueDefault)
	{
		return HermiteInterpolation::selectTemp(
			HermiteInterpolation::selectPoint(x, curve), curve, valueDefault);
	}

	double HermiteInterpolation::getY(double x, const HermiteInterpolation::HermiteTemp temp)
	{
		return HermiteInterpolation::getY(x, temp.x0, temp.x1, temp.y0, temp.y1, temp.d0, temp.d1);
	}

	double HermiteInterpolation::getD(double x, const HermiteInterpolation::HermiteTemp temp)
	{
		return HermiteInterpolation::getD(x, temp.x0, temp.x1, temp.y0, temp.y1, temp.d0, temp.d1);
	}

	double HermiteInterpolation::getY(double x, const Curve* curve, double valueDefault)
	{
		return HermiteInterpolation::getY(x, HermiteInterpolation::selectTemp(x, curve, valueDefault));
	}

	double HermiteInterpolation::getD(double x, const Curve* curve, double valueDefault)
	{
		return HermiteInterpolation::getD(x, HermiteInterpolation::selectTemp(x, curve, valueDefault));
	}

	template<typename Func>
	int HermiteInterpolation::search(int low, int high, Func func)
	{
		int mid = low + (high - low) / 2;
		switch (func(mid))
		{
		case CompareResult::EQ:
			return mid;
		case CompareResult::GTR:
			return HermiteInterpolation::search(mid + 1, high, func);
		case CompareResult::LSS:
			return HermiteInterpolation::search(low, mid - 1, func);
		default:
			return -1;
		}
	}

	//关于埃尔米特插值相关运算的数学推导见文档
	inline double HermiteInterpolation::getY(double x, double x0, double x1, double y0, double y1, double d0, double d1)
	{
		return HermiteInterpolation::getK0(x, x0, x1) * y0 +
			HermiteInterpolation::getK1(x, x0, x1) * y1 +
			HermiteInterpolation::getL0(x, x0, x1) * d0 +
			HermiteInterpolation::getL1(x, x0, x1) * d1;
	}

	inline double HermiteInterpolation::getD(double x, double x0, double x1, double y0, double y1, double d0, double d1)
	{
		return HermiteInterpolation::getDK0(x, x0, x1) * y0 +
			HermiteInterpolation::getDK1(x, x0, x1) * y1 +
			HermiteInterpolation::getDL0(x, x0, x1) * d0 +
			HermiteInterpolation::getDL1(x, x0, x1) * d1;
	}

	inline double HermiteInterpolation::getDeltaX0(double x, double x0)
	{
		return x - x0;
	}

	inline double HermiteInterpolation::getDeltaX1(double x, double x1)
	{
		return x - x1;
	}

	inline double HermiteInterpolation::getDeltaX(double x0, double x1)
	{
		return x1 - x0;
	}

	inline double HermiteInterpolation::getT0(double x, double x0, double x1)
	{
		return HermiteInterpolation::getDeltaX0(x, x0) / HermiteInterpolation::getDeltaX(x0, x1);
	}

	inline double HermiteInterpolation::getT1(double x, double x0, double x1)
	{
		return HermiteInterpolation::getDeltaX1(x, x1) / -HermiteInterpolation::getDeltaX(x0, x1);
	}

	inline double HermiteInterpolation::getK0(double x, double x0, double x1)
	{
		return (1 + 2 * HermiteInterpolation::getT0(x, x0, x1)) * HermiteInterpolation::getT1(x, x0, x1) * HermiteInterpolation::getT1(x, x0, x1);
	}

	inline double HermiteInterpolation::getK1(double x, double x0, double x1)
	{
		return (1 + 2 * HermiteInterpolation::getT1(x, x0, x1)) * HermiteInterpolation::getT0(x, x0, x1) * HermiteInterpolation::getT0(x, x0, x1);
	}

	inline double HermiteInterpolation::getL0(double x, double x0, double x1)
	{
		return HermiteInterpolation::getDeltaX0(x, x0) * HermiteInterpolation::getT1(x, x0, x1) * HermiteInterpolation::getT1(x, x0, x1);
	}

	inline double HermiteInterpolation::getL1(double x, double x0, double x1)
	{
		return HermiteInterpolation::getDeltaX1(x, x1) * HermiteInterpolation::getT0(x, x0, x1) * HermiteInterpolation::getT0(x, x0, x1);
	}

	inline double HermiteInterpolation::getDT0(double x0, double x1)
	{
		return 1 / HermiteInterpolation::getDeltaX(x0, x1);
	}

	inline double HermiteInterpolation::getDT1(double x0, double x1)
	{
		return 1 / -HermiteInterpolation::getDeltaX(x0, x1);
	}

	inline double HermiteInterpolation::getDK0(double x, double x0, double x1)
	{
		return 2 * HermiteInterpolation::getDT0(x0, x1) * HermiteInterpolation::getT1(x, x0, x1) * HermiteInterpolation::getT1(x, x0, x1) +
			(1 + 2 * HermiteInterpolation::getT0(x, x0, x1)) * (2 * HermiteInterpolation::getT1(x, x0, x1) * HermiteInterpolation::getDT1(x0, x1));
	}

	inline double HermiteInterpolation::getDK1(double x, double x0, double x1)
	{
		return 2 * HermiteInterpolation::getDT1(x0, x1) * HermiteInterpolation::getT0(x, x0, x1) * HermiteInterpolation::getT0(x, x0, x1) +
			(1 + 2 * HermiteInterpolation::getT1(x, x0, x1)) * (2 * HermiteInterpolation::getT0(x, x0, x1) * HermiteInterpolation::getDT0(x0, x1));
	}

	inline double HermiteInterpolation::getDL0(double x, double x0, double x1)
	{
		return HermiteInterpolation::getT1(x, x0, x1) * HermiteInterpolation::getT1(x, x0, x1) +
			HermiteInterpolation::getDeltaX0(x, x0) * (2 * HermiteInterpolation::getT1(x, x0, x1) * HermiteInterpolation::getDT1(x0, x1));
	}

	inline double HermiteInterpolation::getDL1(double x, double x0, double x1)
	{
		return HermiteInterpolation::getT0(x, x0, x1) * HermiteInterpolation::getT0(x, x0, x1) +
			HermiteInterpolation::getDeltaX1(x, x1) * (2 * HermiteInterpolation::getT0(x, x0, x1) * HermiteInterpolation::getDT0(x0, x1));
	}
}