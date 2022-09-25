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
				ProtoConverter() = delete;

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

				static bool serilazeToJson(
					const ::vocalshaper::SerializableProjectStructure* object,
					juce::String& result, bool whiteSpace = false
				);

			private:
				struct ColorRGBA
				{
					uint8_t r;
					uint8_t g;
					uint8_t b;
					uint8_t a;
				};

			private:
				template<class T, class P>
				static bool serilazeToJsonInternal(
					const ::vocalshaper::SerializableProjectStructure* object, juce::String& result,
					bool whiteSpace = false);

			public:
				static bool parse(
					const Project* proto,
					::vocalshaper::Project* project);

				static bool parse(
					const Track* proto,
					::vocalshaper::Track* track);

				static bool parse(
					const Label* proto,
					::vocalshaper::Label* label);

				static bool parse(
					const Script* proto,
					::vocalshaper::Script* script);

				static bool parse(
					const Json* proto,
					::vocalshaper::Json* json);

				static bool parse(
					const Curve* proto,
					::vocalshaper::Curve* curve);

				static bool parse(
					const Plugin* proto,
					::vocalshaper::Plugin* plugin);

				static bool parse(
					const Instr* proto,
					::vocalshaper::Instr* instr);

				static bool parse(
					const Note* proto,
					::vocalshaper::Note* note);

				static bool parse(
					const Wave* proto,
					::vocalshaper::Wave* wave);

				static bool parse(
					const Param* proto,
					::vocalshaper::Param* param);

				static bool parse(
					const DPoint* proto,
					::vocalshaper::DPoint* point);

				static bool parse(
					const Phoneme* proto,
					::vocalshaper::Phoneme* phoneme);

				static bool parse(
					const Point* proto,
					::vocalshaper::Point* point);

			public:
				static bool serilaze(
					const ::vocalshaper::Project* project,
					Project* proto);

				static bool serilaze(
					const ::vocalshaper::Track* track,
					Track* proto);

				static bool serilaze(
					const ::vocalshaper::Label* label,
					Label* proto);

				static bool serilaze(
					const ::vocalshaper::Script* script,
					Script* proto);

				static bool serilaze(
					const ::vocalshaper::Json* json,
					Json* proto);

				static bool serilaze(
					const ::vocalshaper::Curve* curve,
					Curve* proto);

				static bool serilaze(
					const ::vocalshaper::Plugin* plugin,
					Plugin* proto);

				static bool serilaze(
					const ::vocalshaper::Note* note,
					Note* proto);

				static bool serilaze(
					const ::vocalshaper::Instr* instr,
					Instr* proto);

				static bool serilaze(
					const ::vocalshaper::Wave* wave,
					Wave* proto);

				static bool serilaze(
					const ::vocalshaper::Param* param,
					Param* proto);

				static bool serilaze(
					const ::vocalshaper::DPoint* point,
					DPoint* proto);

				static bool serilaze(
					const ::vocalshaper::Phoneme* phoneme,
					Phoneme* proto);

				static bool serilaze(
					const ::vocalshaper::Point* point,
					Point* proto);
			};
		}
	}
}
