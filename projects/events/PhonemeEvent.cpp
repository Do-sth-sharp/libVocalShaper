#include "PhonemeEvent.h"
#include "../daos/PhonemeDAO.h"

namespace vocalshaper {
	PhonemeEvent::~PhonemeEvent()
	{
		if (this->ptr) {
			PhonemeDAO::destory(dynamic_cast<Phoneme*>(this->ptr.release()));
		}
	}

	void PhonemeEvent::setTarget(PhonemeEvent::Target target)
	{
		this->target = target;
	}

	const PhonemeEvent::Target PhonemeEvent::getTarget() const
	{
		return this->target;
	}
}