#include "ProtoConverter.h"
#include <google/protobuf/stubs/status.h>
#include <google/protobuf/util/json_util.h>

#define SERILAZE_TO_JSON_CASE_TYPE_RETURN_TRUE(t) \
case ::vocalshaper::SerializableProjectStructure::Type::t: \
{ \
	if (ProtoConverter::serilazeToJsonInternal<::vocalshaper::t, t>(object, result, whiteSpace)) { \
		return true; \
	} \
	break; \
}

#define PARSE_FROM_JSON_CASE_TYPE_RETURN_TRUE(t) \
case ::vocalshaper::SerializableProjectStructure::Type::t: \
{ \
	if (ProtoConverter::parseFromJsonInternal<::vocalshaper::t, t>(json, object)) { \
		return true; \
	} \
	break; \
}

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
					SERILAZE_TO_JSON_CASE_TYPE_RETURN_TRUE(Curve);
					SERILAZE_TO_JSON_CASE_TYPE_RETURN_TRUE(DPoint);
					SERILAZE_TO_JSON_CASE_TYPE_RETURN_TRUE(Instr);
					SERILAZE_TO_JSON_CASE_TYPE_RETURN_TRUE(Json);
					SERILAZE_TO_JSON_CASE_TYPE_RETURN_TRUE(Label);
					SERILAZE_TO_JSON_CASE_TYPE_RETURN_TRUE(Note);
					SERILAZE_TO_JSON_CASE_TYPE_RETURN_TRUE(Param);
					SERILAZE_TO_JSON_CASE_TYPE_RETURN_TRUE(Phoneme);
					SERILAZE_TO_JSON_CASE_TYPE_RETURN_TRUE(Plugin);
					SERILAZE_TO_JSON_CASE_TYPE_RETURN_TRUE(Point);
					SERILAZE_TO_JSON_CASE_TYPE_RETURN_TRUE(Project);
					SERILAZE_TO_JSON_CASE_TYPE_RETURN_TRUE(Script);
					SERILAZE_TO_JSON_CASE_TYPE_RETURN_TRUE(Track);
					SERILAZE_TO_JSON_CASE_TYPE_RETURN_TRUE(Wave);
				}

				return false;
			}

			bool ProtoConverter::parseFromJson(
				const juce::String& json,
				::vocalshaper::SerializableProjectStructure* object
			)
			{
				if (!object) {
					return false;
				}

				switch (object->getType())
				{
					PARSE_FROM_JSON_CASE_TYPE_RETURN_TRUE(Curve);
					PARSE_FROM_JSON_CASE_TYPE_RETURN_TRUE(DPoint);
					PARSE_FROM_JSON_CASE_TYPE_RETURN_TRUE(Instr);
					PARSE_FROM_JSON_CASE_TYPE_RETURN_TRUE(Json);
					PARSE_FROM_JSON_CASE_TYPE_RETURN_TRUE(Label);
					PARSE_FROM_JSON_CASE_TYPE_RETURN_TRUE(Note);
					PARSE_FROM_JSON_CASE_TYPE_RETURN_TRUE(Param);
					PARSE_FROM_JSON_CASE_TYPE_RETURN_TRUE(Phoneme);
					PARSE_FROM_JSON_CASE_TYPE_RETURN_TRUE(Plugin);
					PARSE_FROM_JSON_CASE_TYPE_RETURN_TRUE(Point);
					PARSE_FROM_JSON_CASE_TYPE_RETURN_TRUE(Project);
					PARSE_FROM_JSON_CASE_TYPE_RETURN_TRUE(Script);
					PARSE_FROM_JSON_CASE_TYPE_RETURN_TRUE(Track);
					PARSE_FROM_JSON_CASE_TYPE_RETURN_TRUE(Wave);
				}

				return false;
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

			template<class T, class P>
			static bool ProtoConverter::parseFromJsonInternal(
				const juce::String& json, ::vocalshaper::SerializableProjectStructure* object)
			{
				if (!object) {
					return false;
				}

				std::unique_ptr<P> proto = std::make_unique<P>();
				::google::protobuf::util::JsonParseOptions option;
				option.ignore_unknown_fields = false;
				option.case_insensitive_enum_parsing = false;

				if (!::google::protobuf::util::JsonStringToMessage(
					json.toStdString(), proto.get(), option).ok()) {
					return false;
				}

				if (!ProtoConverter::parse(proto.get(), dynamic_cast<T*>(object))) {
					return false;
				}

				return true;
			}
		}
	}
}