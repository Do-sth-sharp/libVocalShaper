#include "Plugin.h"

#include "../daos/ParamDAO.h"

namespace vocalshaper {
	Plugin::~Plugin()
	{
		while (this->params.size() > 0) {
			ParamDAO::destory(this->params.removeAndReturn(this->params.size() - 1));
		}
	}
}