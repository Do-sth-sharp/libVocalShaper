#include "ProtoConverter.h"

namespace vocalshaper {
	namespace files {
		namespace vsp3 {
			bool ProtoConverter::serilaze(
				const ::vocalshaper::Project* project,
				Project* proto)
			{
				if (!project || !proto) {
					return false;
				}

				proto->set_sample_rate(::vocalshaper::ProjectDAO::getSampleRate(project));
				proto->set_bit_deepth(::vocalshaper::ProjectDAO::getBitDeepth(project));
				proto->set_curve_quantification(::vocalshaper::ProjectDAO::getCurveQuantification(project));

				auto masterTrack = ::vocalshaper::ProjectDAO::getMasterTrack(project);
				if (masterTrack) {
					if (!ProtoConverter::serilaze(masterTrack, proto->mutable_master_track())) {
						return false;
					}
				}

				for (int i = 0; i < ::vocalshaper::ProjectDAO::trackSize(project); i++) {
					auto track = ::vocalshaper::ProjectDAO::getTrack(project, i);
					if (!ProtoConverter::serilaze(track, proto->add_tracks())) {
						return false;
					}
				}

				for (int i = 0; i < ::vocalshaper::ProjectDAO::labelSize(project); i++) {
					auto label = ::vocalshaper::ProjectDAO::getLabel(project, i);
					if (!ProtoConverter::serilaze(label, proto->add_labels())) {
						return false;
					}
				}

				for (int i = 0; i < ::vocalshaper::ProjectDAO::scriptSize(project); i++) {
					auto script = ::vocalshaper::ProjectDAO::getScript(project, i);
					if (!ProtoConverter::serilaze(script, proto->add_scripts())) {
						return false;
					}
				}

				for (int i = 0; i < ::vocalshaper::ProjectDAO::additionSize(project); i++) {
					auto addition = ::vocalshaper::ProjectDAO::getAddition(project, i);
					if (!ProtoConverter::serilaze(addition, proto->add_additions())) {
						return false;
					}
				}

				return true;
			}

			bool ProtoConverter::serilaze(
				const ::vocalshaper::Track* track,
				Track* proto)
			{
				if (!track || !proto) {
					return false;
				}

				switch (::vocalshaper::TrackDAO::getTrackType(track))
				{
				case ::vocalshaper::Track::TrackType::Empty:
					proto->set_track_type(Track::TrackType::Track_TrackType_EMPTY);
					break;
				case ::vocalshaper::Track::TrackType::Voice:
					proto->set_track_type(Track::TrackType::Track_TrackType_VOICE);
					break;
				case ::vocalshaper::Track::TrackType::Midi:
					proto->set_track_type(Track::TrackType::Track_TrackType_MIDI);
					break;
				case ::vocalshaper::Track::TrackType::Wave:
					proto->set_track_type(Track::TrackType::Track_TrackType_WAVE);
					break;
				}

				auto tColor = ::vocalshaper::TrackDAO::getColour(track);
				uint32_t color = 0;
				reinterpret_cast<ProtoConverter::ColorRGBA*>(&color)->r = tColor.getRed();
				reinterpret_cast<ProtoConverter::ColorRGBA*>(&color)->g = tColor.getGreen();
				reinterpret_cast<ProtoConverter::ColorRGBA*>(&color)->b = tColor.getBlue();
				reinterpret_cast<ProtoConverter::ColorRGBA*>(&color)->a = tColor.getAlpha();
				proto->mutable_color()->set_value(color);

				proto->set_solo(::vocalshaper::TrackDAO::getSolo(track));
				proto->set_mute(::vocalshaper::TrackDAO::getMute(track));

				for (int i = 0; i < ::vocalshaper::TrackDAO::curveSize(track); i++) {
					auto curve = ::vocalshaper::TrackDAO::getCurve(track, i);
					if (!ProtoConverter::serilaze(curve, proto->add_curves())) {
						return false;
					}
				}

				for (int i = 0; i < ::vocalshaper::TrackDAO::pluginSize(track); i++) {
					auto plugin = ::vocalshaper::TrackDAO::getPlugin(track, i);
					if (!ProtoConverter::serilaze(plugin, proto->add_plugins())) {
						return false;
					}
				}

				for (int i = 0; i < ::vocalshaper::TrackDAO::noteSize(track); i++) {
					auto note = ::vocalshaper::TrackDAO::getNote(track, i);
					if (!ProtoConverter::serilaze(note, proto->add_notes())) {
						return false;
					}
				}

				proto->set_singer(::vocalshaper::TrackDAO::getSinger(track).toStdString());
				proto->set_style(::vocalshaper::TrackDAO::getStyle(track).toStdString());

				auto instr = ::vocalshaper::TrackDAO::getInstrument(track);
				if (instr) {
					if (!ProtoConverter::serilaze(instr, proto->mutable_instrument())) {
						return false;
					}
				}

				for (int i = 0; i < ::vocalshaper::TrackDAO::waveSize(track); i++) {
					auto wave = ::vocalshaper::TrackDAO::getWave(track, i);
					if (!ProtoConverter::serilaze(wave, proto->add_waves())) {
						return false;
					}
				}

				for (int i = 0; i < ::vocalshaper::TrackDAO::paramSize(track); i++) {
					auto param = ::vocalshaper::TrackDAO::getParam(track, i);
					if (!ProtoConverter::serilaze(param, proto->add_params())) {
						return false;
					}
				}

				return true;
			}

			bool ProtoConverter::serilaze(
				const ::vocalshaper::Label* label,
				Label* proto)
			{
				if (!label || !proto) {
					return false;
				}

				switch (::vocalshaper::LabelDAO::getLabelType(label))
				{
				case ::vocalshaper::Label::LabelType::Lua:
					proto->set_label_type(Label::LabelType::Label_LabelType_LUA);
					break;
				case ::vocalshaper::Label::LabelType::Ini:
					proto->set_label_type(Label::LabelType::Label_LabelType_INI);
					break;
				case ::vocalshaper::Label::LabelType::Xml:
					proto->set_label_type(Label::LabelType::Label_LabelType_XML);
					break;
				case ::vocalshaper::Label::LabelType::Json:
					proto->set_label_type(Label::LabelType::Label_LabelType_JSON);
					break;
				}

				auto position = ::vocalshaper::LabelDAO::getPosition(label);
				proto->mutable_position()->set_beat_pos(position.first);
				proto->mutable_position()->set_deviation(position.second);

				proto->set_data(::vocalshaper::LabelDAO::getData(label).toStdString());

				return true;
			}

			bool ProtoConverter::serilaze(
				const ::vocalshaper::Script* script,
				Script* proto)
			{
				if (!script || !proto) {
					return false;
				}

				switch (::vocalshaper::ScriptDAO::getScriptType(script))
				{
				case ::vocalshaper::Script::ScriptType::Lua:
					proto->set_script_type(Script::ScriptType::Script_ScriptType_LUA);
					break;
				case ::vocalshaper::Script::ScriptType::Js:
					proto->set_script_type(Script::ScriptType::Script_ScriptType_JS);
					break;
				case ::vocalshaper::Script::ScriptType::AIL:
					proto->set_script_type(Script::ScriptType::Script_ScriptType_AIL);
					break;
				}

				proto->set_data(::vocalshaper::ScriptDAO::getData(script).toStdString());
				proto->set_enabled(::vocalshaper::ScriptDAO::getEnabled(script));

				return true;
			}

			bool ProtoConverter::serilaze(
				const ::vocalshaper::Json* json,
				Json* proto)
			{
				if (!json || !proto) {
					return false;
				}

				auto data = ::vocalshaper::JsonDAO::getData(json);
				if (!data) {
					return false;
				}
				proto->set_data(juce::JSON::toString(*data, true).toStdString());

				return true;
			}

			bool ProtoConverter::serilaze(
				const ::vocalshaper::Curve* curve,
				Curve* proto)
			{
				if (!curve || !proto) {
					return false;
				}

				for (int i = 0; i < ::vocalshaper::CurveDAO::pointSize(curve); i++) {
					auto point = ::vocalshaper::CurveDAO::getPoint(curve, i);
					if (!ProtoConverter::serilaze(point, proto->add_points())) {
						return false;
					}
				}

				return true;
			}

			bool ProtoConverter::serilaze(
				const ::vocalshaper::Plugin* plugin,
				Plugin* proto)
			{
				if (!plugin || !proto) {
					return false;
				}

				switch (::vocalshaper::PluginDAO::getPluginType(plugin))
				{
				case ::vocalshaper::Plugin::PluginType::Unknown:
					proto->set_plugin_type(Plugin::PluginType::Plugin_PluginType_UNKNOWN);
					break;
				case ::vocalshaper::Plugin::PluginType::VST:
					proto->set_plugin_type(Plugin::PluginType::Plugin_PluginType_VST);
					break;
				case ::vocalshaper::Plugin::PluginType::VST3:
					proto->set_plugin_type(Plugin::PluginType::Plugin_PluginType_VST3);
					break;
				case ::vocalshaper::Plugin::PluginType::AU:
					proto->set_plugin_type(Plugin::PluginType::Plugin_PluginType_AU);
					break;
				case ::vocalshaper::Plugin::PluginType::LADSPA:
					proto->set_plugin_type(Plugin::PluginType::Plugin_PluginType_LADSPA);
					break;
				case ::vocalshaper::Plugin::PluginType::BuildIn:
					proto->set_plugin_type(Plugin::PluginType::Plugin_PluginType_BUILD_IN);
					break;
				}

				proto->set_unique_id(::vocalshaper::PluginDAO::getUniqueId(plugin));
				proto->set_enabled(::vocalshaper::PluginDAO::getEnabled(plugin));

				for (int i = 0; i < ::vocalshaper::PluginDAO::paramSize(plugin); i++) {
					auto param = ::vocalshaper::PluginDAO::getParam(plugin, i);
					if (!ProtoConverter::serilaze(param, proto->add_params())) {
						return false;
					}
				}

				return true;
			}

			bool ProtoConverter::serilaze(
				const ::vocalshaper::Note* note,
				Note* proto)
			{
				if (!note || !proto) {
					return false;
				}

				switch (::vocalshaper::NoteDAO::getNoteType(note))
				{
				case ::vocalshaper::Note::NoteType::MIDI:
					proto->set_note_type(Note::NoteType::Note_NoteType_MIDI);
					break;
				case ::vocalshaper::Note::NoteType::Voice:
					proto->set_note_type(Note::NoteType::Note_NoteType_VOICE);
					break;
				}

				auto st = ::vocalshaper::NoteDAO::getSt(note);
				proto->mutable_st()->set_beat_pos(st.first);
				proto->mutable_st()->set_deviation(st.second);

				proto->set_length(::vocalshaper::NoteDAO::getLength(note));
				proto->set_pitch(::vocalshaper::NoteDAO::getPitch(note));
				proto->set_tenuto(::vocalshaper::NoteDAO::getTenuto(note));

				proto->set_name(::vocalshaper::NoteDAO::getName(note).toStdString());

				for (int i = 0; i < ::vocalshaper::NoteDAO::phonemeSize(note); i++) {
					auto phoneme = ::vocalshaper::NoteDAO::getPhoneme(note, i);
					if (!ProtoConverter::serilaze(phoneme, proto->add_phonemes())) {
						return false;
					}
				}

				proto->set_flag(::vocalshaper::NoteDAO::getFlag(note).toStdString());

				for (int i = 0; i < ::vocalshaper::NoteDAO::paramSize(note); i++) {
					auto param = ::vocalshaper::NoteDAO::getParam(note, i);
					if (!ProtoConverter::serilaze(param, proto->add_params())) {
						return false;
					}
				}

				return true;
			}

			bool ProtoConverter::serilaze(
				const ::vocalshaper::Instr* instr,
				Instr* proto)
			{
				if (!instr || !proto) {
					return false;
				}

				switch (::vocalshaper::InstrDAO::getInstrType(instr))
				{
				case ::vocalshaper::Instr::InstrType::Unknown:
					proto->set_instr_type(Instr::InstrType::Instr_InstrType_UNKNOWN);
					break;
				case ::vocalshaper::Instr::InstrType::VST:
					proto->set_instr_type(Instr::InstrType::Instr_InstrType_VST);
					break;
				case ::vocalshaper::Instr::InstrType::VST3:
					proto->set_instr_type(Instr::InstrType::Instr_InstrType_VST3);
					break;
				case ::vocalshaper::Instr::InstrType::AU:
					proto->set_instr_type(Instr::InstrType::Instr_InstrType_AU);
					break;
				case ::vocalshaper::Instr::InstrType::LADSPA:
					proto->set_instr_type(Instr::InstrType::Instr_InstrType_LADSPA);
					break;
				}

				proto->set_unique_id(::vocalshaper::InstrDAO::getUniqueId(instr));
				
				for (int i = 0; i < ::vocalshaper::InstrDAO::paramSize(instr); i++) {
					auto param = ::vocalshaper::InstrDAO::getParam(instr, i);
					if (!ProtoConverter::serilaze(param, proto->add_params())) {
						return false;
					}
				}

				return true;
			}

			bool ProtoConverter::serilaze(
				const ::vocalshaper::Wave* wave,
				Wave* proto)
			{
				if (!wave || !proto) {
					return false;
				}

				proto->set_source(::vocalshaper::WaveDAO::getSource(wave).toStdString());
				proto->set_deviation(::vocalshaper::WaveDAO::getDeviation(wave));

				auto st = ::vocalshaper::WaveDAO::getSt(wave);
				proto->mutable_st()->set_beat_pos(st.first);
				proto->mutable_st()->set_deviation(st.second);

				proto->set_length(::vocalshaper::WaveDAO::getLength(wave));

				return true;
			}

			bool ProtoConverter::serilaze(
				const ::vocalshaper::Param* param,
				Param* proto)
			{
				if (!param || !proto) {
					return false;
				}

				switch (::vocalshaper::ParamDAO::getParamType(param))
				{
				case ::vocalshaper::Param::ParamType::Empty:
					proto->set_param_type(Param::ParamType::Param_ParamType_EMPTY);
					break;
				case ::vocalshaper::Param::ParamType::Bool:
					proto->set_param_type(Param::ParamType::Param_ParamType_BOOL);
					proto->mutable_value()->set_bool_data(::vocalshaper::ParamDAO::getBoolData(param));
					break;
				case ::vocalshaper::Param::ParamType::Choice:
					proto->set_param_type(Param::ParamType::Param_ParamType_CHOICE);
					proto->mutable_value()->set_choice_data(::vocalshaper::ParamDAO::getChoiceData(param));
					break;
				case ::vocalshaper::Param::ParamType::Float:
					proto->set_param_type(Param::ParamType::Param_ParamType_FLOAT);
					proto->mutable_value()->set_float_data(::vocalshaper::ParamDAO::getFloatData(param));
					break;
				case ::vocalshaper::Param::ParamType::Int:
					proto->set_param_type(Param::ParamType::Param_ParamType_INT);
					proto->mutable_value()->set_int_data(::vocalshaper::ParamDAO::getIntData(param));
					break;
				}

				proto->set_id(::vocalshaper::ParamDAO::getId(param).toStdString());
				proto->set_controler(::vocalshaper::ParamDAO::getControler(param).toStdString());

				return true;
			}

			bool ProtoConverter::serilaze(
				const ::vocalshaper::DPoint* point,
				DPoint* proto)
			{
				if (!point || !proto) {
					return false;
				}

				auto x = ::vocalshaper::DPointDAO::getTime(point);
				proto->mutable_x()->set_beat_pos(x.first);
				proto->mutable_x()->set_deviation(x.second);

				proto->set_y(::vocalshaper::DPointDAO::getY(point));
				proto->set_dl(::vocalshaper::DPointDAO::getDl(point));
				proto->set_dr(::vocalshaper::DPointDAO::getDr(point));

				return true;
			}

			bool ProtoConverter::serilaze(
				const ::vocalshaper::Phoneme* phoneme,
				Phoneme* proto)
			{
				if (!phoneme || !proto) {
					return false;
				}

				proto->set_deviation(::vocalshaper::PhonemeDAO::getDeviation(phoneme));
				proto->set_name(::vocalshaper::PhonemeDAO::getName(phoneme).toStdString());
				proto->set_is_pre(::vocalshaper::PhonemeDAO::getIsPre(phoneme));

				for (int i = 0; i < ::vocalshaper::PhonemeDAO::timePointSize(phoneme); i++) {
					auto point = ::vocalshaper::PhonemeDAO::getTimePoint(phoneme, i);
					if (!ProtoConverter::serilaze(point, proto->add_time_map())) {
						return false;
					}
				}

				return true;
			}

			bool ProtoConverter::serilaze(
				const ::vocalshaper::Point* point,
				Point* proto)
			{
				if (!point || !proto) {
					return false;
				}

				proto->set_x(::vocalshaper::PointDAO::getX(point));
				proto->set_y(::vocalshaper::PointDAO::getY(point));

				return true;
			}
		}
	}
}