#include "InstrDAO.h"

namespace vocalshaper {
	Instr::InstrType InstrDAO::getInstrType(const Instr* ptr)
	{
		if (!ptr) {
			return Instr::InstrType::Unknown;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->instrType;
	}

	int InstrDAO::getUniqueId(const Instr* ptr)
	{
		if (!ptr) {
			return -1;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->uniqueId;
	}

	void InstrDAO::setUniqueId(Instr* ptr, int uniqueId)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		if (ptr->uniqueId == uniqueId) {
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
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->params.size();
	}

	Param* InstrDAO::getParam(const Instr* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedReadLock locker(ptr->lock);
		return ptr->params[index];
	}

	Param* InstrDAO::insertParam(Instr* ptr, int index, Param* param)
	{
		if (!ptr || !param) {
			return nullptr;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = false;
		return ptr->params.insert(index, param);
	}

	Param* InstrDAO::releaseParam(Instr* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = false;
		return ptr->params.removeAndReturn(index);
	}

	bool InstrDAO::isSaved(const Instr* ptr)
	{
		if (!ptr) {
			return true;
		}
		juce::ScopedReadLock locker(ptr->lock);
		if (!ptr->saved) {
			return false;
		}
		for (auto i : ptr->params) {
			if (!ParamDAO::isSaved(i)) {
				return false;
			}
		}
		return true;
	}

	void InstrDAO::save(Instr* ptr)
	{
		if (!ptr) {
			return;
		}
		juce::ScopedWriteLock locker(ptr->lock);
		ptr->saved = true;
		for (auto i : ptr->params) {
			ParamDAO::save(i);
		}
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