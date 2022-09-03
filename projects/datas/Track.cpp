#include "Track.h"

#include "../daos/CurveDAO.h"
#include "../daos/PluginDAO.h"
#include "../daos/NoteDAO.h"
#include "../daos/WaveDAO.h"
#include "../daos/ParamDAO.h"

namespace vocalshaper {
	Track::~Track()
	{
		while (this->curves.size() > 0) {
			CurveDAO::destory(this->curves.removeAndReturn(this->curves.size() - 1));
		}
		while (this->plugins.size() > 0) {
			PluginDAO::destory(this->plugins.removeAndReturn(this->plugins.size() - 1));
		}
		while (this->notes.size() > 0) {
			NoteDAO::destory(this->notes.removeAndReturn(this->notes.size() - 1));
		}
		while (this->waves.size() > 0) {
			WaveDAO::destory(this->waves.removeAndReturn(this->waves.size() - 1));
		}
		while (this->params.size() > 0) {
			ParamDAO::destory(this->params.removeAndReturn(this->params.size() - 1));
		}
	}
}