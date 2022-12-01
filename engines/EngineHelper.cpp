#include "EngineHelper.h"
#include "../projects/daos/TrackDAO.h"
#include "../projects/curve/HermiteInterpolation.h"

namespace vocalshaper {
	const Curve* EngineHelper::findCurve(const Track* track, const juce::String& id)
	{
		for (int i = 0; i < vocalshaper::TrackDAO::curveSize(track); i++) {
			auto curve = vocalshaper::TrackDAO::getCurve(track, i);
			if (curve) {
				if (vocalshaper::CurveDAO::getId(curve) == id) {
					return curve;
				}
			}
		}
		return nullptr;
	}

	const Param* EngineHelper::findParam(const Track* track, const juce::String& id)
	{
		for (int i = 0; i < vocalshaper::TrackDAO::paramSize(track); i++) {
			auto param = vocalshaper::TrackDAO::getParam(track, i);
			if (param) {
				if (vocalshaper::ParamDAO::getId(param) == id) {
					return param;
				}
			}
		}
		return nullptr;
	}

	const Param* EngineHelper::findParam(const Note* note, const juce::String& id)
	{
		for (int i = 0; i < vocalshaper::NoteDAO::paramSize(note); i++) {
			auto param = vocalshaper::NoteDAO::getParam(note, i);
			if (param) {
				if (vocalshaper::ParamDAO::getId(param) == id) {
					return param;
				}
			}
		}
		return nullptr;
	}

	const juce::String EngineHelper::makeFullID(const juce::String& shortID)
	{
		return "VocalShaper.Engine." + shortID;
	}

	const ParamInfo EngineHelper::findParamInfo(
		const ParamInfoList& list, const juce::String& shortID)
	{
		for (auto& i : list) {
			if (i.id == shortID) {
				return i;
			}
		}
		return ParamInfo();
	}
}