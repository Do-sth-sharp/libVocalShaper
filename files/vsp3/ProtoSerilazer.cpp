#include "ProtoConverter.h"

namespace vocalshaper {
	namespace files {
		namespace vsp3 {
			bool ProtoConverter::serilazeProject(
				const ::vocalshaper::Project* project,
				Project* proto)
			{
				if (!project || !proto) {
					return false;
				}

				proto->set_sample_rate(ProjectDAO::getSampleRate(project));
				proto->set_bit_deepth(ProjectDAO::getBitDeepth(project));
				proto->set_curve_quantification(ProjectDAO::getCurveQuantification(project));

				auto masterTrack = ProjectDAO::getMasterTrack(project);
				if (masterTrack) {
					if (!ProtoConverter::serilazeTrack(masterTrack, proto->mutable_master_track())) {
						return false;
					}
				}

				for (int i = 0; i < ProjectDAO::trackSize(project); i++) {
					auto track = ProjectDAO::getTrack(project, i);
					if (!ProtoConverter::serilazeTrack(track, proto->add_tracks())) {
						return false;
					}
				}

				for (int i = 0; i < ProjectDAO::labelSize(project); i++) {
					auto label = ProjectDAO::getLabel(project, i);
					if (!ProtoConverter::serilazeLabel(label, proto->add_labels())) {
						return false;
					}
				}

				for (int i = 0; i < ProjectDAO::scriptSize(project); i++) {
					auto script = ProjectDAO::getScript(project, i);
					if (!ProtoConverter::serilazeScript(script, proto->add_scripts())) {
						return false;
					}
				}

				for (int i = 0; i < ProjectDAO::additionSize(project); i++) {
					auto addition = ProjectDAO::getAddition(project, i);
					if (!ProtoConverter::serilazeJson(addition, proto->add_additions())) {
						return false;
					}
				}

				return true;
			}

			bool ProtoConverter::serilazeTrack(
				const ::vocalshaper::Track* track,
				Track* proto)
			{
				if (!track || !proto) {
					return false;
				}
				return true;
			}

			bool ProtoConverter::serilazeLabel(
				const ::vocalshaper::Label* label,
				Label* proto)
			{
				if (!label || !proto) {
					return false;
				}
				return true;
			}

			bool ProtoConverter::serilazeScript(
				const ::vocalshaper::Script* script,
				Script* proto)
			{
				if (!script || !proto) {
					return false;
				}
				return true;
			}

			bool ProtoConverter::serilazeJson(
				const ::vocalshaper::Json* json,
				Json* proto)
			{
				if (!json || !proto) {
					return false;
				}
				return true;
			}
		}
	}
}