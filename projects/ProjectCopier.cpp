#include "ProjectCopier.h"
#include "daos/ProjectDAO.h"

namespace vocalshaper {
	Project* ProjectCopier::copyProject(const Project* ptr)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedReadLock locker(ptr->lock);
		auto dst = new Project;
		if (!dst) {
			return nullptr;
		}

		dst->sampleRate = ptr->sampleRate;
		dst->bitDeepth = ptr->bitDeepth;
		dst->curveQuantification = ptr->curveQuantification;

		dst->masterTrack.reset(ProjectCopier::copyTrack(ptr->masterTrack.get()));

		for (auto i : ptr->tracks) {
			dst->tracks.add(ProjectCopier::copyTrack(i));
		}

		for (auto i : ptr->labels) {
			dst->labels.add(ProjectCopier::copyLabel(i));
		}

		for (auto i : ptr->scripts) {
			dst->scripts.add(ProjectCopier::copyScript(i));
		}

		for (auto i : ptr->additions) {
			dst->additions.add(ProjectCopier::copyJson(i));
		}

		return dst;
	}

	Track* ProjectCopier::copyTrack(const Track* ptr)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedReadLock locker(ptr->lock);
		auto dst = new Track;
		if (!dst) {
			return nullptr;
		}

		dst->trackType = ptr->trackType;
		dst->color = ptr->color;
		dst->solo = ptr->solo;
		dst->mute = ptr->mute;
		dst->singer = ptr->singer;
		dst->style = ptr->style;

		dst->instrument.reset(ProjectCopier::copyInstr(ptr->instrument.get()));

		for (auto i : ptr->curves) {
			dst->curves.add(ProjectCopier::copyCurve(i));
		}

		for (auto i : ptr->plugins) {
			dst->plugins.add(ProjectCopier::copyPlugin(i));
		}

		for (auto i : ptr->notes) {
			dst->notes.add(ProjectCopier::copyNote(i));
		}

		for (auto i : ptr->waves) {
			dst->waves.add(ProjectCopier::copyWave(i));
		}

		for (auto i : ptr->params) {
			dst->params.add(ProjectCopier::copyParam(i));
		}

		return dst;
	}

	Label* ProjectCopier::copyLabel(const Label* ptr)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedReadLock locker(ptr->lock);
		auto dst = new Label;
		if (!dst) {
			return nullptr;
		}

		dst->labelType = ptr->labelType;
		dst->position = ptr->position;
		dst->data = ptr->data;

		return dst;
	}

	Script* ProjectCopier::copyScript(const Script* ptr)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedReadLock locker(ptr->lock);
		auto dst = new Script;
		if (!dst) {
			return nullptr;
		}

		dst->scriptType = ptr->scriptType;
		dst->data = ptr->data;
		dst->enabled = ptr->enabled;

		return dst;
	}

	Json* ProjectCopier::copyJson(const Json* ptr)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedReadLock locker(ptr->lock);
		auto dst = new Json;
		if (!dst) {
			return nullptr;
		}

		dst->data = ptr->data;

		return dst;
	}

	Instr* ProjectCopier::copyInstr(const Instr* ptr)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedReadLock locker(ptr->lock);
		auto dst = new Instr(ptr->instrType);
		if (!dst) {
			return nullptr;
		}

		dst->instrType = ptr->instrType;
		dst->uniqueId = ptr->uniqueId;

		for (auto i : ptr->params) {
			dst->params.add(ProjectCopier::copyParam(i));
		}

		return dst;
	}

	Curve* ProjectCopier::copyCurve(const Curve* ptr)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedReadLock locker(ptr->lock);
		auto dst = new Curve;
		if (!dst) {
			return nullptr;
		}

		for (auto i : ptr->points) {
			dst->points.add(ProjectCopier::copyDPoint(i));
		}

		return dst;
	}

	Plugin* ProjectCopier::copyPlugin(const Plugin* ptr)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedReadLock locker(ptr->lock);
		auto dst = new Plugin(ptr->pluginType);
		if (!dst) {
			return nullptr;
		}

		dst->pluginType = ptr->pluginType;
		dst->uniqueId = ptr->uniqueId;
		dst->enabled = ptr->enabled;

		for (auto i : ptr->params) {
			dst->params.add(ProjectCopier::copyParam(i));
		}

		return dst;
	}

	Note* ProjectCopier::copyNote(const Note* ptr)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedReadLock locker(ptr->lock);
		auto dst = new Note(ptr->noteType);
		if (!dst) {
			return nullptr;
		}

		dst->noteType = ptr->noteType;
		dst->st = ptr->st;
		dst->length = ptr->length;
		dst->pitch = ptr->pitch;
		dst->tenuto = ptr->tenuto;
		dst->name = ptr->name;

		for (auto i : ptr->phonemes) {
			dst->phonemes.add(ProjectCopier::copyPhoneme(i));
		}

		dst->flag = ptr->flag;

		for (auto i : ptr->params) {
			dst->params.add(ProjectCopier::copyParam(i));
		}

		return dst;
	}

	Wave* ProjectCopier::copyWave(const Wave* ptr)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedReadLock locker(ptr->lock);
		auto dst = new Wave;
		if (!dst) {
			return nullptr;
		}

		dst->source = ptr->source;
		dst->deviation = ptr->deviation;
		dst->st = ptr->st;
		dst->length = ptr->length;

		return dst;
	}

	Param* ProjectCopier::copyParam(const Param* ptr)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedReadLock locker(ptr->lock);
		auto dst = new Param(ptr->paramType);
		if (!dst) {
			return nullptr;
		}

		dst->paramType = ptr->paramType;
		dst->id = ptr->id;
		dst->value = ptr->value;
		dst->controler = ptr->controler;

		return dst;
	}

	DPoint* ProjectCopier::copyDPoint(const DPoint* ptr)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedReadLock locker(ptr->lock);
		auto dst = new DPoint;
		if (!dst) {
			return nullptr;
		}

		dst->x = ptr->x;
		dst->y = ptr->y;
		dst->dl = ptr->dl;
		dst->dr = ptr->dr;

		return dst;
	}

	Phoneme* ProjectCopier::copyPhoneme(const Phoneme* ptr)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedReadLock locker(ptr->lock);
		auto dst = new Phoneme;
		if (!dst) {
			return nullptr;
		}

		dst->deviation = ptr->deviation;
		dst->name = ptr->name;
		dst->isPre = ptr->isPre;

		for (auto i : ptr->timeMap) {
			dst->timeMap.add(ProjectCopier::copyPoint(i));
		}

		return dst;
	}

	Point* ProjectCopier::copyPoint(const Point* ptr)
	{
		if (!ptr) {
			return nullptr;
		}
		juce::ScopedReadLock locker(ptr->lock);
		auto dst = new Point;
		if (!dst) {
			return nullptr;
		}

		dst->x = ptr->x;
		dst->y = ptr->y;

		return dst;
	}
}