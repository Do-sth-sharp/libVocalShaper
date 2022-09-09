#pragma once
#include "../Macros.h"

#include <JuceHeader.h>
#include "datas/Project.h"

namespace vocalshaper {
	class VSAPI ProjectCopier
	{
		ProjectCopier() = delete;

	public:
		static Project* copyProject(const Project* ptr);
		static Track* copyTrack(const Track* ptr);
		static Label* copyLabel(const Label* ptr);
		static Script* copyScript(const Script* ptr);
		static Json* copyJson(const Json* ptr);
		static Instr* copyInstr(const Instr* ptr);
		static Curve* copyCurve(const Curve* ptr);
		static Plugin* copyPlugin(const Plugin* ptr);
		static Note* copyNote(const Note* ptr);
		static Wave* copyWave(const Wave* ptr);
		static Param* copyParam(const Param* ptr);
		static DPoint* copyDPoint(const DPoint* ptr);
		static Phoneme* copyPhoneme(const Phoneme* ptr);
		static Point* copyPoint(const Point* ptr);
	};
}