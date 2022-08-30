#include "InstrDAO.h"

namespace vocalshaper {
	Instr::InstrType InstrDAO::getInstrType(const Instr* ptr)
	{
		if (!ptr) {
			return Instr::InstrType::Unknown;
		}
		return ptr->instrType;
	}

	int InstrDAO::getUniqueId(const Instr* ptr)
	{
		if (!ptr) {
			return 0;
		}
		return ptr->uniqueId;
	}

	void InstrDAO::setUniqueId(Instr* ptr, int uniqueId)
	{
		if (!ptr) {
			return;
		}
		ptr->saved = false;
		ptr->uniqueId = uniqueId;
	}

	int InstrDAO::paramSize(const Instr* ptr)
	{
		if (!ptr) {
			return -1;
		}
		return ptr->params.size();
	}

	Param* InstrDAO::getParam(const Instr* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		return ptr->params[index];
	}

	Param* InstrDAO::insertParam(Instr* ptr, int index, Param* point)
	{
		if (!ptr || !point) {
			return nullptr;
		}
		ptr->saved = false;
		return ptr->params.insert(index, point);
	}

	Param* InstrDAO::releaseParam(Instr* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		ptr->saved = false;
		return ptr->params.removeAndReturn(index);
	}

	bool InstrDAO::isSaved(const Instr* ptr)
	{
		return true;
	}

	void InstrDAO::save(Instr* ptr)
	{

	}

	Instr* InstrDAO::create(Instr::InstrType type)
	{
		auto ptr = new Instr;
		ptr->instrType = type;
		return ptr;
	}

	void InstrDAO::destory(Instr* ptr)
	{
		delete ptr;
	}
}