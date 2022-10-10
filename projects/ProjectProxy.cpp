#include "ProjectProxy.h"
#include "daos/ProjectDAO.h"

namespace vocalshaper {
	ProjectProxy::ProjectProxy(const juce::String& name, const juce::String& path)
		:name(name), path(path)
	{
		this->ptrData = std::make_unique<Project>();
		this->ptrMeta = std::make_unique<ProjectMeta>();
		this->eventProcesser = std::make_unique<EventProcesser>(this);
		this->labelTemp = std::make_unique<LabelTemp>(this);
		this->tempoTemp = std::make_unique<TempoTemp>(this->labelTemp.get());
	}

	const juce::String& ProjectProxy::getName() const
	{
		return this->name;
	}

	const juce::String& ProjectProxy::getPath() const
	{
		return this->path;
	}

	bool ProjectProxy::getSaved() const
	{
		return ProjectDAO::isSaved(this->ptrData.get());
	}

	Project* ProjectProxy::getPtr()
	{
		return this->ptrData.get();
	}

	ProjectMeta* ProjectProxy::getMeta()
	{
		return this->ptrMeta.get();
	}

	EventProcesser* ProjectProxy::getProcesser()
	{
		return this->eventProcesser.get();
	}

	const TempoTemp* ProjectProxy::getTempo()
	{
		return this->tempoTemp.get();
	}

	const juce::ReadWriteLock& ProjectProxy::getLock() const
	{
		return this->lock;
	}

	void ProjectProxy::changeUrl(const juce::String& name, const juce::String& path)
	{
		this->name = name;
		this->path = path;
	}

	void ProjectProxy::refreshLabels()
	{
		this->labelTemp->refresh();
		this->tempoTemp->refresh();
	}
}