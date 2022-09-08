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

	void WaveEvent::setPtr(Wave* ptr)
	{
		if (this->ptr1) {
			WaveDAO::destory(this->ptr1.release());
		}
		this->ptr1.reset(ptr);
	}

	Wave* WaveEvent::getPtr() const
	{
		return this->ptr1.get();
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