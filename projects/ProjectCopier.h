#pragma once
#include "../Macros.h"

#include <JuceHeader.h>
#include "datas/Project.h"

namespace vocalshaper {
	class VSAPI ProjectCopier
	{
		ProjectCopier() = delete;

	public:
		static SerializableProjectStructure* copy(const SerializableProjectStructure* ptr);

		static Project* copy(const Project* ptr);
		static Track* copy(const Track* ptr);
		static Label* copy(const Label* ptr);
		static Script* copy(const Script* ptr);
		static Json* copy(const Json* ptr);
		static Instr* copy(const Instr* ptr);
		static Curve* copy(const Curve* ptr);
		static Plugin* copy(const Plugin* ptr);
		static Note* copy(const Note* ptr);
		static Wave* copy(const Wave* ptr);
		static Param* copy(const Param* ptr);
		static DPoint* copy(const DPoint* ptr);
		static Phoneme* copy(const Phoneme* ptr);
		static Point* copy(const Point* ptr);
	};
}