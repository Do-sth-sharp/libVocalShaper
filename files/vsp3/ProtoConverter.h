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
				//project必须为新建立的未经修改的
				static bool parseFromProto(
					const Project* proto,
					::vocalshaper::Project* project,
					::vocalshaper::ProjectMeta::MetaObject* meta);

				//proto必须为新建立的未经修改的
				static bool serilazeToProto(
					const ::vocalshaper::Project* project,
					const ::vocalshaper::ProjectMeta::MetaObject* meta,
					Project* proto);

			private:
				struct ColorRGBA
				{
					uint8_t r;
					uint8_t g;
					uint8_t b;
					uint8_t a;
				};

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

				static bool parseDPoint(
					const DPoint* proto,
					::vocalshaper::DPoint* point);

				static bool parsePhoneme(
					const Phoneme* proto,
					::vocalshaper::Phoneme* phoneme);

				static bool parsePoint(
					const Point* proto,
					::vocalshaper::Point* point);

			private:
				static bool serilazeProject(
					const ::vocalshaper::Project* project,
					Project* proto);

				static bool serilazeTrack(
					const ::vocalshaper::Track* track,
					Track* proto);

				static bool serilazeLabel(
					const ::vocalshaper::Label* label,
					Label* proto);

				static bool serilazeScript(
					const ::vocalshaper::Script* script,
					Script* proto);

				static bool serilazeJson(
					const ::vocalshaper::Json* json,
					Json* proto);

				static bool serilazeCurve(
					const ::vocalshaper::Curve* curve,
					Curve* proto);

				static bool serilazePlugin(
					const ::vocalshaper::Plugin* plugin,
					Plugin* proto);

				static bool serilazeNote(
					const ::vocalshaper::Note* note,
					Note* proto);

				static bool serilazeInstr(
					const ::vocalshaper::Instr* instr,
					Instr* proto);

				static bool serilazeWave(
					const ::vocalshaper::Wave* wave,
					Wave* proto);

				static bool serilazeParam(
					const ::vocalshaper::Param* param,
					Param* proto);

				static bool serilazeDPoint(
					const ::vocalshaper::DPoint* point,
					DPoint* proto);

				static bool serilazePhoneme(
					const ::vocalshaper::Phoneme* phoneme,
					Phoneme* proto);

				static bool serilazePoint(
					const ::vocalshaper::Point* point,
					Point* proto);
			};
		}
	}
}
