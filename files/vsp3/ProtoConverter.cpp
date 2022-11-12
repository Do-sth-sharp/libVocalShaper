#include "ProtoConverter.h"
#include "proto_out/Project.pb.h"
#include <absl/status/status.h>
#include <google/protobuf/util/json_util.h>
//克隆项目后阅读源码前请进行一次生成，将解决报错问题

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

#define PARSE_FROM_JSON_RETURN_UNIQUE_PTR(t) \
{ \
	auto ptr = std::make_unique<::vocalshaper::t>(); \
	if (ProtoConverter::parseFromJsonInternal<::vocalshaper::t, t>(json, ptr.get())) { \
		return std::move(ptr); \
	} \
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
				if (proto->version() > VS_PROJECT_VERSION ||
					proto->version() < VS_PROJECT_MIN_VERSION) {
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

			std::unique_ptr<::vocalshaper::SerializableProjectStructure>
				ProtoConverter::parseFromJsonWithUnknownType(const juce::String& json)
			{
				PARSE_FROM_JSON_RETURN_UNIQUE_PTR(Project);
				PARSE_FROM_JSON_RETURN_UNIQUE_PTR(Track);
				//PARSE_FROM_JSON_RETURN_UNIQUE_PTR(Note);
				{
					std::unique_ptr<Note> proto = std::make_unique<Note>();

					if (ProtoConverter::parseFromJsonInternalToProto(json, proto.get())) {
						std::unique_ptr<::vocalshaper::Note> ptr = nullptr;

						switch (proto->note_type()) {
						case Note::NoteType::Note_NoteType_VOICE:
						{
							ptr = std::make_unique<::vocalshaper::Note>(::vocalshaper::Note::NoteType::Voice);
							break;
						}
						case Note::NoteType::Note_NoteType_MIDI:
						{
							ptr = std::make_unique<::vocalshaper::Note>(::vocalshaper::Note::NoteType::MIDI);
							break;
						}
						}

						if (!ProtoConverter::parse(proto.get(), ptr.get())) {
							return std::move(ptr);
						}
					}
				}
				PARSE_FROM_JSON_RETURN_UNIQUE_PTR(Phoneme);
				PARSE_FROM_JSON_RETURN_UNIQUE_PTR(Wave);
				PARSE_FROM_JSON_RETURN_UNIQUE_PTR(Label);
				PARSE_FROM_JSON_RETURN_UNIQUE_PTR(Script);
				//PARSE_FROM_JSON_RETURN_UNIQUE_PTR(Plugin);
				{
					std::unique_ptr<Plugin> proto = std::make_unique<Plugin>();

					if (ProtoConverter::parseFromJsonInternalToProto(json, proto.get())) {
						std::unique_ptr<::vocalshaper::Plugin> ptr = nullptr;

						switch (proto->plugin_type()) {
						case Plugin::PluginType::Plugin_PluginType_UNKNOWN:
						{
							ptr = std::make_unique<::vocalshaper::Plugin>(::vocalshaper::Plugin::PluginType::Unknown);
							break;
						}
						case Plugin::PluginType::Plugin_PluginType_VST:
						{
							ptr = std::make_unique<::vocalshaper::Plugin>(::vocalshaper::Plugin::PluginType::VST);
							break;
						}
						case Plugin::PluginType::Plugin_PluginType_VST3:
						{
							ptr = std::make_unique<::vocalshaper::Plugin>(::vocalshaper::Plugin::PluginType::VST3);
							break;
						}
						case Plugin::PluginType::Plugin_PluginType_AU:
						{
							ptr = std::make_unique<::vocalshaper::Plugin>(::vocalshaper::Plugin::PluginType::AU);
							break;
						}
						case Plugin::PluginType::Plugin_PluginType_LADSPA:
						{
							ptr = std::make_unique<::vocalshaper::Plugin>(::vocalshaper::Plugin::PluginType::LADSPA);
							break;
						}
						case Plugin::PluginType::Plugin_PluginType_BUILD_IN:
						{
							ptr = std::make_unique<::vocalshaper::Plugin>(::vocalshaper::Plugin::PluginType::BuildIn);
							break;
						}
						}

						if (!ProtoConverter::parse(proto.get(), ptr.get())) {
							return std::move(ptr);
						}
					}
				}
				PARSE_FROM_JSON_RETURN_UNIQUE_PTR(Curve);
				PARSE_FROM_JSON_RETURN_UNIQUE_PTR(DPoint);
				PARSE_FROM_JSON_RETURN_UNIQUE_PTR(Point);
				//PARSE_FROM_JSON_RETURN_UNIQUE_PTR(Param);
				{
					std::unique_ptr<Param> proto = std::make_unique<Param>();

					if (ProtoConverter::parseFromJsonInternalToProto(json, proto.get())) {
						std::unique_ptr<::vocalshaper::Param> ptr = nullptr;

						switch (proto->param_type()) {
						case Param::ParamType::Param_ParamType_EMPTY:
						{
							ptr = std::make_unique<::vocalshaper::Param>(::vocalshaper::Param::ParamType::Empty);
							break;
						}
						case Param::ParamType::Param_ParamType_BOOL:
						{
							ptr = std::make_unique<::vocalshaper::Param>(::vocalshaper::Param::ParamType::Bool);
							break;
						}
						case Param::ParamType::Param_ParamType_CHOICE:
						{
							ptr = std::make_unique<::vocalshaper::Param>(::vocalshaper::Param::ParamType::Choice);
							break;
						}
						case Param::ParamType::Param_ParamType_FLOAT:
						{
							ptr = std::make_unique<::vocalshaper::Param>(::vocalshaper::Param::ParamType::Float);
							break;
						}
						case Param::ParamType::Param_ParamType_INT:
						{
							ptr = std::make_unique<::vocalshaper::Param>(::vocalshaper::Param::ParamType::Int);
							break;
						}
						}

						if (!ProtoConverter::parse(proto.get(), ptr.get())) {
							return std::move(ptr);
						}
					}
				}
				PARSE_FROM_JSON_RETURN_UNIQUE_PTR(Json);
				//PARSE_FROM_JSON_RETURN_UNIQUE_PTR(Instr);
				{
					std::unique_ptr<Instr> proto = std::make_unique<Instr>();

					if (ProtoConverter::parseFromJsonInternalToProto(json, proto.get())) {
						std::unique_ptr<::vocalshaper::Instr> ptr = nullptr;

						switch (proto->instr_type()) {
						case Instr::InstrType::Instr_InstrType_UNKNOWN:
						{
							ptr = std::make_unique<::vocalshaper::Instr>(::vocalshaper::Instr::InstrType::Unknown);
							break;
						}
						case Instr::InstrType::Instr_InstrType_VST:
						{
							ptr = std::make_unique<::vocalshaper::Instr>(::vocalshaper::Instr::InstrType::VST);
							break;
						}
						case Instr::InstrType::Instr_InstrType_VST3:
						{
							ptr = std::make_unique<::vocalshaper::Instr>(::vocalshaper::Instr::InstrType::VST3);
							break;
						}
						case Instr::InstrType::Instr_InstrType_AU:
						{
							ptr = std::make_unique<::vocalshaper::Instr>(::vocalshaper::Instr::InstrType::AU);
							break;
						}
						case Instr::InstrType::Instr_InstrType_LADSPA:
						{
							ptr = std::make_unique<::vocalshaper::Instr>(::vocalshaper::Instr::InstrType::LADSPA);
							break;
						}
						}

						if (!ProtoConverter::parse(proto.get(), ptr.get())) {
							return std::move(ptr);
						}
					}
				}

				return nullptr;
			}

			template<class T, class P>
			bool ProtoConverter::serilazeToJsonInternal(
				const ::vocalshaper::SerializableProjectStructure* object, juce::String& result, bool whiteSpace)
			{
				std::unique_ptr<P> proto = std::make_unique<P>();
				if (!ProtoConverter::serilaze(dynamic_cast<const T*>(object), proto.get())) {
					return false;
				}

				return ProtoConverter::serilazeToJsonInternalFromProto(proto.get(), result, whiteSpace);
			}

			template<class T, class P>
			static bool ProtoConverter::parseFromJsonInternal(
				const juce::String& json, ::vocalshaper::SerializableProjectStructure* object)
			{
				if (!object) {
					return false;
				}

				std::unique_ptr<P> proto = std::make_unique<P>();

				if (!ProtoConverter::parseFromJsonInternalToProto(json, proto.get())) {
					return false;
				}

				if (!ProtoConverter::parse(proto.get(), dynamic_cast<T*>(object))) {
					return false;
				}

				return true;
			}

			template<class P>
			static bool ProtoConverter::serilazeToJsonInternalFromProto(
				const P* proto, juce::String& result,
				bool whiteSpace)
			{
				if (!proto) {
					return false;
				}

				std::string resultTemp;
				::google::protobuf::util::JsonOptions option;
				option.add_whitespace = whiteSpace;
				option.always_print_primitive_fields = false;
				option.always_print_enums_as_ints = false;
				option.preserve_proto_field_names = true;

				if (!::google::protobuf::util::MessageToJsonString(
					*proto, &resultTemp, option).ok()) {
					return false;
				}

				result = resultTemp;
				return true;
			}

			template<class P>
			static bool ProtoConverter::parseFromJsonInternalToProto(
				const juce::String& json, P* proto)
			{
				if (!proto) {
					return false;
				}

				::google::protobuf::util::JsonParseOptions option;
				option.ignore_unknown_fields = false;
				option.case_insensitive_enum_parsing = false;

				return ::google::protobuf::util::JsonStringToMessage(
					json.toStdString(), proto, option).ok();
			}
		}
	}
}