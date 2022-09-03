#include "ProtoConverter.h"

namespace vocalshaper {
	namespace files {
		namespace vsp3 {
			struct ColorRGBA
			{
				uint8_t r;
				uint8_t g;
				uint8_t b;
				uint8_t a;
			};

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

				for (int i = 0; i < proto->scripts_size(); i++) {
					auto script = ScriptDAO::create();
					if (!ProtoConverter::parseScript(&proto->scripts(i), script)) {
						return false;
					}
					if (!ProjectDAO::insertScript(project, i, script)) {
						return false;
					}
				}

				for (int i = 0; i < proto->additions_size(); i++) {
					auto json = JsonDAO::create();
					if (!ProtoConverter::parseJson(&proto->additions(i), json)) {
						return false;
					}
					if (!ProjectDAO::insertAddition(project, i, json)) {
						return false;
					}
				}

				return true;
			}

			bool ProtoConverter::parseTrack(
				const Track* proto,
				::vocalshaper::Track* track)
			{
				if (!proto || !track) {
					return false;
				}

				uint32_t trackcolor = proto->color().value();
				TrackDAO::setColour(track,
					juce::Colour::fromRGBA(
						reinterpret_cast<ColorRGBA*>(&trackcolor)->r,
						reinterpret_cast<ColorRGBA*>(&trackcolor)->g,
						reinterpret_cast<ColorRGBA*>(&trackcolor)->b,
						reinterpret_cast<ColorRGBA*>(&trackcolor)->a
					));
				TrackDAO::setSolo(track, proto->solo());
				TrackDAO::setMute(track, proto->solo());

				for (int i = 0; i < proto->curves_size(); i++) {
					auto curve = CurveDAO::create();
					if (!ProtoConverter::parseCurve(&proto->curves(i), curve)) {
						return false;
					}
					if (!TrackDAO::insertCurve(track, i, curve)) {
						return false;
					}
				}

				for (int i = 0; i < proto->plugins_size(); i++) {
					auto pluginType = ::vocalshaper::Plugin::PluginType::Unknown;
					auto& refProto = proto->plugins(i);
					switch (refProto.plugin_type())
					{
					case Plugin::PluginType::Plugin_PluginType_VST:
						pluginType = ::vocalshaper::Plugin::PluginType::VST;
						break;
					case Plugin::PluginType::Plugin_PluginType_VST3:
						pluginType = ::vocalshaper::Plugin::PluginType::VST3;
						break;
					case Plugin::PluginType::Plugin_PluginType_AU:
						pluginType = ::vocalshaper::Plugin::PluginType::AU;
						break;
					case Plugin::PluginType::Plugin_PluginType_LADSPA:
						pluginType = ::vocalshaper::Plugin::PluginType::LADSPA;
						break;
					case Plugin::PluginType::Plugin_PluginType_BUILD_IN:
						pluginType = ::vocalshaper::Plugin::PluginType::BuildIn;
						break;
					default:
						break;
					}
					auto plugin = PluginDAO::create(pluginType);
					if (!ProtoConverter::parsePlugin(&refProto, plugin)) {
						return false;
					}
					if (!TrackDAO::insertPlugin(track, i, plugin)) {
						return false;
					}
				}

				//如果有保存instrument，说明储存前轨道有乐器，有乐器即是midi轨
				if (proto->has_instrument()) {
					auto instrType = ::vocalshaper::Instr::InstrType::Unknown;
					auto& refProto = proto->instrument();
					switch (refProto.instr_type())
					{
					case Instr::InstrType::Instr_InstrType_VST:
						instrType = ::vocalshaper::Instr::InstrType::VST;
						break;
					case Instr::InstrType::Instr_InstrType_VST3:
						instrType = ::vocalshaper::Instr::InstrType::VST3;
						break;
					case Instr::InstrType::Instr_InstrType_AU:
						instrType = ::vocalshaper::Instr::InstrType::AU;
						break;
					case Instr::InstrType::Instr_InstrType_LADSPA:
						instrType = ::vocalshaper::Instr::InstrType::LADSPA;
						break;
					default:
						break;
					}
					auto instr = InstrDAO::create(instrType);
					if (!ProtoConverter::parseInstr(&refProto, instr)) {
						return false;
					}
					if (!TrackDAO::setInstrument(track, instr)) {
						return false;
					}
				}
				//存在轨道无乐器，有音符，但依然是midi轨的可能
				if (proto->track_type() == Track::TrackType::Track_TrackType_MIDI) {
					track->trackType = ::vocalshaper::Track::TrackType::Midi;
				}

				//如轨道不为midi轨，但有音符，则自动设为voice轨
				for (int i = 0; i < proto->notes_size(); i++) {
					auto noteType = ::vocalshaper::Note::NoteType::MIDI;
					auto& refProto = proto->notes(i);
					switch (refProto.note_type())
					{
					case Note::NoteType::Note_NoteType_VOICE:
						noteType = ::vocalshaper::Note::NoteType::Voice;
						break;
					default:
						break;
					}
					auto note = NoteDAO::create(noteType);
					if (!ProtoConverter::parseNote(&refProto, note)) {
						return false;
					}
					if (!TrackDAO::insertNote(track, i, note)) {
						return false;
					}
				}

				TrackDAO::setSinger(track, proto->singer());
				TrackDAO::setStyle(track, proto->style());

				//如有wave，则是wave轨
				for (int i = 0; i < proto->waves_size(); i++) {
					auto wave = WaveDAO::create();
					if (!ProtoConverter::parseWave(&proto->waves(i), wave)) {
						return false;
					}
					if (!TrackDAO::insertWave(track, i, wave)) {
						return false;
					}
				}

				for (int i = 0; i < proto->params_size(); i++) {
					auto paramType = ::vocalshaper::Param::ParamType::Empty;
					auto& refProto = proto->params(i);
					switch (refProto.param_type())
					{
					case Param::ParamType::Param_ParamType_BOOL:
						paramType = ::vocalshaper::Param::ParamType::Bool;
						break;
					case Param::ParamType::Param_ParamType_CHOICE:
						paramType = ::vocalshaper::Param::ParamType::Choice;
						break;
					case Param::ParamType::Param_ParamType_FLOAT:
						paramType = ::vocalshaper::Param::ParamType::Float;
						break;
					case Param::ParamType::Param_ParamType_INT:
						paramType = ::vocalshaper::Param::ParamType::Int;
						break;
					default:
						break;
					}
					auto param = ParamDAO::create(paramType);
					if (!ProtoConverter::parseParam(&refProto, param)) {
						return false;
					}
					if (!TrackDAO::insertParam(track, i, param)) {
						return false;
					}
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

			bool ProtoConverter::parseScript(
				const Script* proto,
				::vocalshaper::Script* script)
			{
				if (!proto || !script) {
					return false;
				}
				return true;
			}

			bool ProtoConverter::parseJson(
				const Json* proto,
				::vocalshaper::Json* json)
			{
				if (!proto || !json) {
					return false;
				}
				return true;
			}

			bool ProtoConverter::parseCurve(
				const Curve* proto,
				::vocalshaper::Curve* curve)
			{
				if (!proto || !curve) {
					return false;
				}
				return true;
			}

			bool ProtoConverter::parsePlugin(
				const Plugin* proto,
				::vocalshaper::Plugin* plugin)
			{
				if (!proto || !plugin) {
					return false;
				}
				return true;
			}

			bool ProtoConverter::parseInstr(
				const Instr* proto,
				::vocalshaper::Instr* instr)
			{
				if (!proto || !instr) {
					return false;
				}
				return true;
			}

			bool ProtoConverter::parseNote(
				const Note* proto,
				::vocalshaper::Note* note)
			{
				if (!proto || !note) {
					return false;
				}
				return true;
			}

			bool ProtoConverter::parseWave(
				const Wave* proto,
				::vocalshaper::Wave* wave)
			{
				if (!proto || !wave) {
					return false;
				}
				return true;
			}

			bool ProtoConverter::parseParam(
				const Param* proto,
				::vocalshaper::Param* param)
			{
				if (!proto || !param) {
					return false;
				}
				return true;
			}
		}
	}
}