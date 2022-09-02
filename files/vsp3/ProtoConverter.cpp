#include "ProtoConverter.h"

namespace vocalshaper {
	namespace files {
		namespace vsp3 {
			bool ProtoConverter::parseFromProto(
				const Project* proto, ::vocalshaper::Project* project,
				::vocalshaper::ProjectMeta::MetaObject* meta)
			{
				if (!proto || !project || !meta) {
					return false;
				}

				//check version
				if (proto->version() > VS_PROJECT_VERSION) {
					return false;
				}

				//parse meta
				meta->createEditor = proto->editor_create();
				meta->saveEditor = proto->editor_save();
				meta->timeSpent = proto->time_spent();
				meta->createTime = proto->create_time();
				meta->saveTime = proto->save_time();
				meta->version = proto->version();

				//parse data
				if (!ProtoConverter::parseProject(proto, project)) {
					return false;
				}

				ProjectDAO::save(project);
				return true;
			}

			bool ProtoConverter::serilazeToProto(
				const ::vocalshaper::Project* project,
				const ::vocalshaper::ProjectMeta::MetaObject* meta, Project* proto)
			{
				if (!project || !meta || !proto) {
					return false;
				}
				return true;
			}

			bool ProtoConverter::parseProject(
				const Project* proto,
				::vocalshaper::Project* project)
			{
				if (!proto || !project) {
					return false;
				}

				ProjectDAO::setSampleRate(project, proto->sample_rate());
				ProjectDAO::setBitDeepth(project, proto->bit_deepth());
				ProjectDAO::setCurveQuantification(project, proto->curve_quantification());

				auto masterTrack = ProjectDAO::getMasterTrack(project);
				if (!proto->has_master_track()) {
					return false;
				}
				if (!ProtoConverter::parseTrack(&proto->master_track(), masterTrack)) {
					return false;
				}

				for (int i = 0; i < proto->tracks_size(); i++) {
					auto track = TrackDAO::create();
					if (!ProtoConverter::parseTrack(&proto->tracks(i), track)) {
						return false;
					}
					if (!ProjectDAO::insertTrack(project, i, track)) {
						return false;
					}
				}

				for (int i = 0; i < proto->labels_size(); i++) {
					auto label = LabelDAO::create();
					if (!ProtoConverter::parseLabel(&proto->labels(i), label)) {
						return false;
					}
					if (!ProjectDAO::insertLabel(project, i, label)) {
						return false;
					}
				}

				// TODO

				return true;
			}

			bool ProtoConverter::parseTrack(
				const Track* proto,
				::vocalshaper::Track* track)
			{
				if (!proto || !track) {
					return false;
				}
				return true;
			}

			bool ProtoConverter::parseLabel(
				const Label* proto,
				::vocalshaper::Label* label)
			{
				if (!proto || !label) {
					return false;
				}
				return true;
			}
		}
	}
}