#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "Project.pb.h"
#include "../../projects/daos/ProjectDAO.h"
#include "../../projects/datas/Project.h"
#include "../../projects/ProjectMeta.h"

namespace vocalshaper {
	namespace files {
		namespace vsp3 {
			class VSAPI ProtoConverter
			{
			public:
				static bool parseFromProto(
					const Project* proto,
					::vocalshaper::Project* project,
					::vocalshaper::ProjectMeta::MetaObject* meta);

				static bool serilazeToProto(
					const ::vocalshaper::Project* project,
					const ::vocalshaper::ProjectMeta::MetaObject* meta,
					Project* proto);

			private:
				static bool parseProject(
					const Project* proto,
					::vocalshaper::Project* project);
				static bool parseTrack(
					const Track* proto,
					::vocalshaper::Track* track);
				static bool parseLabel(
					const Label* proto,
					::vocalshaper::Label* label);
			};
		}
	}
}
