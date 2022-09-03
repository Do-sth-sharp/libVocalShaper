#include "Phoneme.h"

#include "../daos/PointDAO.h"

namespace vocalshaper {
	Phoneme::~Phoneme()
	{
		while (this->timeMap.size() > 0) {
			PointDAO::destory(this->timeMap.removeAndReturn(this->timeMap.size() - 1));
		}
	}
}