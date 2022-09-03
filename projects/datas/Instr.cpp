#include "Instr.h"

#include "../daos/ParamDAO.h"

namespace vocalshaper {
	Instr::~Instr()
	{
		while (this->params.size() > 0) {
			ParamDAO::destory(this->params.removeAndReturn(this->params.size() - 1));
		}
	}
}