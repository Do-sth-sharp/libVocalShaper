#include "Curve.h"

#include "../daos/DPointDAO.h"

namespace vocalshaper {
	Curve::~Curve()
	{
		while (this->points.size() > 0) {
			DPointDAO::destory(this->points.removeAndReturn(this->points.size() - 1));
		}
	}
}