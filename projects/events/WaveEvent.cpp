#include "WaveEvent.h"
#include "../daos/WaveDAO.h"

namespace vocalshaper {
	WaveEvent::~WaveEvent()
	{
		if (this->ptr) {
			WaveDAO::destory(dynamic_cast<Wave*>(this->ptr.release()));
		}
	}

	void WaveEvent::setTarget(WaveEvent::Target target)
	{
		this->target = target;
	}

	const WaveEvent::Target WaveEvent::getTarget() const
	{
		return this->target;
	}
}