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

				return true;
			}

			bool ProtoConverter::serilazeToProto(
				const ::vocalshaper::Project* project,
				const ::vocalshaper::ProjectMeta::MetaObject* meta, Project* proto)
			{
				if (!project || !meta || !proto) {
					return false;
				}

				//serilaze meta
				proto->set_editor_create(meta->createEditor.toStdString());
				proto->set_editor_save(meta->saveEditor.toStdString());
				proto->set_time_spent(meta->timeSpent);
				proto->set_create_time(meta->createTime);
				proto->set_save_time(meta->saveTime);
				proto->set_version(meta->version);

				//serilaze data
				if (!ProtoConverter::serilazeProject(project, proto)) {
					return false;
				}

				return true;
			}
		}
	}
}