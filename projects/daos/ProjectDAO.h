#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "../datas/Project.h"
#include "TrackDAO.h"
#include "LabelDAO.h"
#include "ScriptDAO.h"
#include "JsonDAO.h"

namespace vocalshaper {
	class VSAPI ProjectDAO
	{
		ProjectDAO() = default;

	public:
		static uint32_t getSampleRate(const Project* ptr);
		static void setSampleRate(Project* ptr, uint32_t sampleRate);
		static uint32_t getBitDeepth(const Project* ptr);
		static void setBitDeepth(Project* ptr, uint32_t bitDeepth);
		static uint32_t getCurveQuantification(const Project* ptr);
		static void setCurveQuantification(Project* ptr, uint32_t curveQuantification);

		static Track* getMasterTrack(const Project* ptr);

		static int trackSize(const Project* ptr);
		static Track* getTrack(const Project* ptr, int index);
		static Track* insertTrack(Project* ptr, int index, Track* track);
		static Track* releaseTrack(Project* ptr, int index);

		static int labelSize(const Project* ptr);
		static Label* getLabel(const Project* ptr, int index);
		static Label* insertLabel(Project* ptr, int index, Label* label);
		static Label* releaseLabel(Project* ptr, int index);

		static int scriptSize(const Project* ptr);
		static Script* getScript(const Project* ptr, int index);
		static Script* insertScript(Project* ptr, int index, Script* script);
		static Script* releaseScript(Project* ptr, int index);

		static int additionSize(const Project* ptr);
		static Json* getAddition(const Project* ptr, int index);
		static Json* insertAddition(Project* ptr, int index, Json* addition);
		static Json* releaseAddition(Project* ptr, int index);

	public:
		static bool isSaved(const Project* ptr);
		static void save(Project* ptr);

	public:
		static Project* create();
		static void destory(Project* ptr);
	};
}