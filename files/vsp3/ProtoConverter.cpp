#include "ProtoConverter.h"
#include <google/protobuf/stubs/status.h>
#include <google/protobuf/util/json_util.h>

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
				if (!ProtoConverter::parse(proto, project)) {
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
				if (!ProtoConverter::serilaze(project, proto)) {
					return false;
				}

				return true;
			}

			bool ProtoConverter::serilazeToJson(
				const ::vocalshaper::SerializableProjectStructure* object,
				juce::String& result, bool whiteSpace
			)
			{
				if (!object) {
					return false;
				}

				switch (object->getType())
				{
				case ::vocalshaper::SerializableProjectStructure::Type::Curve:
				{
					if (!ProtoConverter::serilazeToJsonInternal<::vocalshaper::Curve, Curve>(object, result, whiteSpace)) {
						return false;
					}
					break;
				}
				case ::vocalshaper::SerializableProjectStructure::Type::DPoint:
				{
					if (!ProtoConverter::serilazeToJsonInternal<::vocalshaper::DPoint, DPoint>(object, result, whiteSpace)) {
						return false;
					}
					break;
				}
				case ::vocalshaper::SerializableProjectStructure::Type::Instr:
				{
					if (!ProtoConverter::serilazeToJsonInternal<::vocalshaper::Instr, Instr>(object, result, whiteSpace)) {
						return false;
					}
					break;
				}
				case ::vocalshaper::SerializableProjectStructure::Type::Json:
				{
					if (!ProtoConverter::serilazeToJsonInternal<::vocalshaper::Json, Json>(object, result, whiteSpace)) {
						return false;
					}
					break;
				}
				case ::vocalshaper::SerializableProjectStructure::Type::Label:
				{
					if (!ProtoConverter::serilazeToJsonInternal<::vocalshaper::Label, Label>(object, result, whiteSpace)) {
						return false;
					}
					break;
				}
				case ::vocalshaper::SerializableProjectStructure::Type::Note:
				{
					if (!ProtoConverter::serilazeToJsonInternal<::vocalshaper::Note, Note>(object, result, whiteSpace)) {
						return false;
					}
					break;
				}
				case ::vocalshaper::SerializableProjectStructure::Type::Param:
				{
					if (!ProtoConverter::serilazeToJsonInternal<::vocalshaper::Param, Param>(object, result, whiteSpace)) {
						return false;
					}
					break;
				}
				case ::vocalshaper::SerializableProjectStructure::Type::Phoneme:
				{
					if (!ProtoConverter::serilazeToJsonInternal<::vocalshaper::Phoneme, Phoneme>(object, result, whiteSpace)) {
						return false;
					}
					break;
				}
				case ::vocalshaper::SerializableProjectStructure::Type::Plugin:
				{
					if (!ProtoConverter::serilazeToJsonInternal<::vocalshaper::Plugin, Plugin>(object, result, whiteSpace)) {
						return false;
					}
					break;
				}
				case ::vocalshaper::SerializableProjectStructure::Type::Point:
				{
					if (!ProtoConverter::serilazeToJsonInternal<::vocalshaper::Point, Point>(object, result, whiteSpace)) {
						return false;
					}
					break;
				}
				case ::vocalshaper::SerializableProjectStructure::Type::Project:
				{
					if (!ProtoConverter::serilazeToJsonInternal<::vocalshaper::Project, Project>(object, result, whiteSpace)) {
						return false;
					}
					break;
				}
				case ::vocalshaper::SerializableProjectStructure::Type::Script:
				{
					if (!ProtoConverter::serilazeToJsonInternal<::vocalshaper::Script, Script>(object, result, whiteSpace)) {
						return false;
					}
					break;
				}
				case ::vocalshaper::SerializableProjectStructure::Type::Track:
				{
					if (!ProtoConverter::serilazeToJsonInternal<::vocalshaper::Track, Track>(object, result, whiteSpace)) {
						return false;
					}
					break;
				}
				case ::vocalshaper::SerializableProjectStructure::Type::Wave:
				{
					if (!ProtoConverter::serilazeToJsonInternal<::vocalshaper::Wave, Wave>(object, result, whiteSpace)) {
						return false;
					}
					break;
				}
				}

				return true;
			}

			template<class T, class P>
			bool ProtoConverter::serilazeToJsonInternal(
				const ::vocalshaper::SerializableProjectStructure* object, juce::String& result, bool whiteSpace)
			{
				std::unique_ptr<P> proto = std::make_unique<P>();
				if (!ProtoConverter::serilaze(dynamic_cast<const T*>(object), proto.get())) {
					return false;
				}

				std::string resultTemp;
				::google::protobuf::util::JsonOptions option;
				option.add_whitespace = whiteSpace;
				option.always_print_primitive_fields = false;
				option.always_print_enums_as_ints = false;
				option.preserve_proto_field_names = true;

				if (!::google::protobuf::util::MessageToJsonString(
					*(proto.get()), &resultTemp, option).ok()) {
					return false;
				}

				result = resultTemp;
				return true;
			}
		}
	}
}