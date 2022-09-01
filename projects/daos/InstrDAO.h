#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "../datas/Instr.h"
#include "ParamDAO.h"

namespace vocalshaper {
	class VSAPI InstrDAO
	{
		InstrDAO() = default;

	public:
		static Instr::InstrType getInstrType(const Instr* ptr);

		static int getUniqueId(const Instr* ptr);
		static void setUniqueId(Instr* ptr, int uniqueId);

		static int paramSize(const Instr* ptr);
		static Param* getParam(const Instr* ptr, int index);
		static Param* insertParam(Instr* ptr, int index, Param* param);
		static Param* releaseParam(Instr* ptr, int index);

	public:
		static bool isSaved(const Instr* ptr);
		static void save(Instr* ptr);

	public:
		static Instr* create(Instr::InstrType type);
		static void destory(Instr* ptr);
	};
}