#include "ProtoConverter.h"

namespace vocalshaper {
	namespace files {
		namespace vsp3 {
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
						reinterpret_cast<ProtoConverter::ColorRGBA*>(&trackcolor)->r,
						reinterpret_cast<ProtoConverter::ColorRGBA*>(&trackcolor)->g,
						reinterpret_cast<ProtoConverter::ColorRGBA*>(&trackcolor)->b,
						reinterpret_cast<ProtoConverter::ColorRGBA*>(&trackcolor)->a
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

				switch (proto->label_type())
				{
				case Label::LabelType::Label_LabelType_LUA:
					LabelDAO::setLabelType(label, ::vocalshaper::Label::LabelType::Lua);
					break;
				case Label::LabelType::Label_LabelType_INI:
					LabelDAO::setLabelType(label, ::vocalshaper::Label::LabelType::Ini);
					break;
				case Label::LabelType::Label_LabelType_XML:
					LabelDAO::setLabelType(label, ::vocalshaper::Label::LabelType::Xml);
					break;
				case Label::LabelType::Label_LabelType_JSON:
					LabelDAO::setLabelType(label, ::vocalshaper::Label::LabelType::Json);
					break;
				default:
					break;
				}

				LabelDAO::setPosition(label, ::vocalshaper::make_time(
					proto->position().beat_pos(), proto->position().deviation()));
				LabelDAO::setData(label, proto->data());

				return true;
			}

			bool ProtoConverter::parseScript(
				const Script* proto,
				::vocalshaper::Script* script)
			{
				if (!proto || !script) {
					return false;
				}

				switch (proto->script_type())
				{
				case Script::ScriptType::Script_ScriptType_LUA:
					ScriptDAO::setScriptType(script, ::vocalshaper::Script::ScriptType::Lua);
					break;
				case Script::ScriptType::Script_ScriptType_JS:
					ScriptDAO::setScriptType(script, ::vocalshaper::Script::ScriptType::Js);
					break;
				case Script::ScriptType::Script_ScriptType_AIL:
					ScriptDAO::setScriptType(script, ::vocalshaper::Script::ScriptType::AIL);
					break;
				default:
					break;
				}

				ScriptDAO::setData(script, proto->data());
				ScriptDAO::setEnabled(script, proto->enabled());

				return true;
			}

			bool ProtoConverter::parseJson(
				const Json* proto,
				::vocalshaper::Json* json)
			{
				if (!proto || !json) {
					return false;
				}

				if (!juce::JSON::parse(proto->data(), (*JsonDAO::getDataMutable(json)))) {
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

				for (int i = 0; i < proto->points_size(); i++) {
					auto point = DPointDAO::create();
					if (!ProtoConverter::parseDPoint(&proto->points(i), point)) {
						return false;
					}
					if (!CurveDAO::insertPoint(curve, i, point)) {
						return false;
					}
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

				PluginDAO::setUniqueId(plugin, proto->unique_id());
				PluginDAO::setEnabled(plugin, proto->enabled());

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
					if (!PluginDAO::insertParam(plugin, i, param)) {
						return false;
					}
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

				InstrDAO::setUniqueId(instr, proto->unique_id());

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
					if (!InstrDAO::insertParam(instr, i, param)) {
						return false;
					}
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

				NoteDAO::setSt(note, ::vocalshaper::make_time(
					proto->st().beat_pos(), proto->st().deviation()));
				NoteDAO::setLength(note, proto->length());
				NoteDAO::setPitch(note, proto->pitch());
				NoteDAO::setTenuto(note, proto->tenuto());

				NoteDAO::setName(note, proto->name());

				for (int i = 0; i < proto->phonemes_size(); i++) {
					auto phoneme = PhonemeDAO::create();
					if (!ProtoConverter::parsePhoneme(&proto->phonemes(i), phoneme)) {
						return false;
					}
					if (!NoteDAO::insertPhoneme(note, i, phoneme)) {
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
					if (!NoteDAO::insertParam(note, i, param)) {
						return false;
					}
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

				WaveDAO::setSource(wave, proto->source());
				WaveDAO::setDeviation(wave, proto->deviation());
				WaveDAO::setSt(wave, ::vocalshaper::make_time(
					proto->st().beat_pos(), proto->st().deviation()));
				WaveDAO::setLength(wave, proto->length());

				return true;
			}

			bool ProtoConverter::parseParam(
				const Param* proto,
				::vocalshaper::Param* param)
			{
				if (!proto || !param) {
					return false;
				}

				ParamDAO::setId(param, proto->id());

				switch (proto->param_type())
				{
				case Param::ParamType::Param_ParamType_BOOL:
					ParamDAO::setBoolData(param, proto->value().bool_data());
					break;
				case Param::ParamType::Param_ParamType_CHOICE:
					ParamDAO::setBoolData(param, proto->value().choice_data());
					break;
				case Param::ParamType::Param_ParamType_FLOAT:
					ParamDAO::setBoolData(param, proto->value().float_data());
					break;
				case Param::ParamType::Param_ParamType_INT:
					ParamDAO::setBoolData(param, proto->value().int_data());
					break;
				default:
					break;
				}

				ParamDAO::setControler(param, proto->controler());

				return true;
			}

			bool ProtoConverter::parseDPoint(
				const DPoint* proto,
				::vocalshaper::DPoint* point)
			{
				if (!proto || !point) {
					return false;
				}

				DPointDAO::setTime(point, ::vocalshaper::make_time(
					proto->x().beat_pos(), proto->x().deviation()));
				DPointDAO::setY(point, proto->y());
				DPointDAO::setDl(point, proto->dl());
				DPointDAO::setDr(point, proto->dr());

				return true;
			}

			bool ProtoConverter::parsePhoneme(
				const Phoneme* proto,
				::vocalshaper::Phoneme* phoneme)
			{
				if (!proto || !phoneme) {
					return false;
				}

				PhonemeDAO::setDeviation(phoneme, proto->deviation());
				PhonemeDAO::setName(phoneme, proto->name());
				PhonemeDAO::setIsPre(phoneme, proto->is_pre());

				for (int i = 0; i < proto->time_map_size(); i++) {
					auto point = PointDAO::create();
					if (!ProtoConverter::parsePoint(&proto->time_map(i), point)) {
						return false;
					}
					if (!PhonemeDAO::insertTimePoint(phoneme, i, point)) {
						return false;
					}
				}

				return true;
			}

			bool ProtoConverter::parsePoint(
				const Point* proto,
				::vocalshaper::Point* point)
			{
				if (!proto || !point) {
					return false;
				}

				PointDAO::setX(point, proto->x());
				PointDAO::setY(point, proto->y());

				return true;
			}
		}
	}
}