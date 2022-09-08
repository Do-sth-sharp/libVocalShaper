#include "PhonemeEvent.h"
#include "../daos/PhonemeDAO.h"

namespace vocalshaper {
	PhonemeEvent::~PhonemeEvent()
	{
		if (this->ptr1) {
			PhonemeDAO::destory(this->ptr1.release());
		}
		if (this->ptr2) {
			PhonemeDAO::destory(this->ptr2.release());
		}
	}

	void PhonemeEvent::setPtr(Phoneme* ptr)
	{
		if (this->ptr1) {
			PhonemeDAO::destory(this->ptr1.release());
		}
		this->ptr1.reset(ptr);
	}

	Phoneme* PhonemeEvent::getPtr() const
	{
		return this->ptr1.get();
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