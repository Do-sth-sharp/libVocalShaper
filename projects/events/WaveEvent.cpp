#include "WaveEvent.h"
#include "../daos/WaveDAO.h"

namespace vocalshaper {
	WaveEvent::~WaveEvent()
	{
		if (this->ptr1) {
			WaveDAO::destory(this->ptr1.release());
		}
		if (this->ptr2) {
			WaveDAO::destory(this->ptr2.release());
		}
	}
}