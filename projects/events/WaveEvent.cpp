#include "WaveEvent.h"
#include "../daos/WaveDAO.h"

namespace vocalshaper {
	void WaveEvent::setTarget(WaveEvent::Target target)
	{
		this->target = target;
	}

	const WaveEvent::Target WaveEvent::getTarget() const
	{
		return this->target;
	}
}