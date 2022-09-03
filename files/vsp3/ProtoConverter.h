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

				static bool parseScript(
					const Script* proto,
					::vocalshaper::Script* script);

				static bool parseJson(
					const Json* proto,
					::vocalshaper::Json* json);

				static bool parseCurve(
					const Curve* proto,
					::vocalshaper::Curve* curve);

				static bool parsePlugin(
					const Plugin* proto,
					::vocalshaper::Plugin* plugin);

				static bool parseInstr(
					const Instr* proto,
					::vocalshaper::Instr* instr);

				static bool parseNote(
					const Note* proto,
					::vocalshaper::Note* note);

				static bool parseWave(
					const Wave* proto,
					::vocalshaper::Wave* wave);

				static bool parseParam(
					const Param* proto,
					::vocalshaper::Param* param);
			};
		}
	}
}
