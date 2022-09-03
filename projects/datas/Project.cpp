#include "Project.h"

#include "../daos/TrackDAO.h"
#include "../daos/LabelDAO.h"
#include "../daos/ScriptDAO.h"
#include "../daos/JsonDAO.h"

namespace vocalshaper {
	Project::~Project()
	{
		while (this->tracks.size() > 0) {
			TrackDAO::destory(this->tracks.removeAndReturn(this->tracks.size() - 1));
		}
		while (this->labels.size() > 0) {
			LabelDAO::destory(this->labels.removeAndReturn(this->labels.size() - 1));
		}
		while (this->scripts.size() > 0) {
			ScriptDAO::destory(this->scripts.removeAndReturn(this->scripts.size() - 1));
		}
		while (this->additions.size() > 0) {
			JsonDAO::destory(this->additions.removeAndReturn(this->additions.size() - 1));
		}
		if (this->masterTrack) {
			TrackDAO::destory(this->masterTrack.release());
		}
	}
}