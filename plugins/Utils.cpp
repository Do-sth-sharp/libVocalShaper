#include "Utils.h"

namespace vocalshaper {
	double adsorb(double x, AdsorbState state)
	{
		if (state == AdsorbState::AdsorbOff) {
			return x;
		}

		int adsorb = static_cast<int>(state);
		double granularity = 1. / adsorb;

		double base = std::floor(x);
		double mod = x - base;

		int times = std::round(mod / granularity);
		return base + granularity * times;
	}
}