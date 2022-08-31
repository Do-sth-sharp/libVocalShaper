#include "ProjectDAO.h"

namespace vocalshaper {
	uint32_t ProjectDAO::getSampleRate(const Project* ptr)
	{
		if (!ptr) {
			return 0;
		}
		return ptr->sampleRate;
	}

	void ProjectDAO::setSampleRate(Project* ptr, uint32_t sampleRate)
	{
		if (!ptr) {
			return;
		}
		ptr->saved = false;
		ptr->sampleRate = sampleRate;
	}

	uint32_t ProjectDAO::getBitDeepth(const Project* ptr)
	{
		if (!ptr) {
			return 0;
		}
		return ptr->bitDeepth;
	}

	void ProjectDAO::setBitDeepth(Project* ptr, uint32_t bitDeepth)
	{
		if (!ptr) {
			return;
		}
		ptr->saved = false;
		ptr->bitDeepth = bitDeepth;
	}

	uint32_t ProjectDAO::getCurveQuantification(const Project* ptr)
	{
		if (!ptr) {
			return 0;
		}
		return ptr->curveQuantification;
	}

	void ProjectDAO::setCurveQuantification(Project* ptr, uint32_t curveQuantification)
	{
		if (!ptr) {
			return;
		}
		ptr->saved = false;
		ptr->curveQuantification = curveQuantification;
	}

	Track* ProjectDAO::getMasterTrack(const Project* ptr)
	{
		if (!ptr) {
			return nullptr;
		}
		return ptr->masterTrack.get();
	}

	int ProjectDAO::trackSize(const Project* ptr)
	{
		if (!ptr) {
			return -1;
		}
		return ptr->tracks.size();
	}

	Track* ProjectDAO::getTrack(const Project* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		return ptr->tracks[index];
	}

	Track* ProjectDAO::insertTrack(Project* ptr, int index, Track* track)
	{
		if (!ptr || !track) {
			return nullptr;
		}
		ptr->saved = false;
		return ptr->tracks.insert(index, track);
	}

	Track* ProjectDAO::releaseTrack(Project* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		ptr->saved = false;
		return ptr->tracks.removeAndReturn(index);
	}

	int ProjectDAO::labelSize(const Project* ptr)
	{
		if (!ptr) {
			return -1;
		}
		return ptr->labels.size();
	}

	Label* ProjectDAO::getLabel(const Project* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		return ptr->labels[index];
	}

	Label* ProjectDAO::insertLabel(Project* ptr, int index, Label* label)
	{
		if (!ptr || !label) {
			return nullptr;
		}
		ptr->saved = false;
		return ptr->labels.insert(index, label);
	}

	Label* ProjectDAO::releaseLabel(Project* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		ptr->saved = false;
		return ptr->labels.removeAndReturn(index);
	}

	int ProjectDAO::scriptSize(const Project* ptr)
	{
		if (!ptr) {
			return -1;
		}
		return ptr->scripts.size();
	}

	Script* ProjectDAO::getScript(const Project* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		return ptr->scripts[index];
	}

	Script* ProjectDAO::insertScript(Project* ptr, int index, Script* script)
	{
		if (!ptr || !script) {
			return nullptr;
		}
		ptr->saved = false;
		return ptr->scripts.insert(index, script);
	}

	Script* ProjectDAO::releaseScript(Project* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		ptr->saved = false;
		return ptr->scripts.removeAndReturn(index);
	}

	int ProjectDAO::additionSize(const Project* ptr)
	{
		if (!ptr) {
			return -1;
		}
		return ptr->additions.size();
	}

	Json* ProjectDAO::getAddition(const Project* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		return ptr->additions[index];
	}

	Json* ProjectDAO::insertAddition(Project* ptr, int index, Json* addition)
	{
		if (!ptr || !addition) {
			return nullptr;
		}
		ptr->saved = false;
		return ptr->additions.insert(index, addition);
	}

	Json* ProjectDAO::releaseAddition(Project* ptr, int index)
	{
		if (!ptr) {
			return nullptr;
		}
		ptr->saved = false;
		return ptr->additions.removeAndReturn(index);
	}

	bool ProjectDAO::isSaved(const Project* ptr)
	{
		return true;
	}

	void ProjectDAO::save(Project* ptr)
	{

	}

	Project* ProjectDAO::create()
	{
		auto ptr = new Project;
		//TODO
		return ptr;
	}

	void ProjectDAO::destory(Project* ptr)
	{
		delete ptr;
	}
}