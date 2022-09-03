#include "Note.h"

#include "../daos/PhonemeDAO.h"
#include "../daos/ParamDAO.h"

namespace vocalshaper {
	Note::~Note()
	{
		while (this->phonemes.size() > 0) {
			PhonemeDAO::destory(this->phonemes.removeAndReturn(this->phonemes.size() - 1));
		}
		while (this->params.size() > 0) {
			ParamDAO::destory(this->params.removeAndReturn(this->params.size() - 1));
		}
	}
}