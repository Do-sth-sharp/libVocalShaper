#include "ProjectProxy.h"
#include "daos/ProjectDAO.h"

namespace vocalshaper {
	ProjectProxy::ProjectProxy(const juce::String& name, const juce::String& path)
		:name(name), path(path)
	{
		this->ptrData = std::unique_ptr<Project, std::function<void(Project*)>>(
			ProjectDAO::create(), ProjectDAO::destory);
		this->ptrMeta = std::make_unique<ProjectMeta>();
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

	const Project* ProjectProxy::getPtr() const
	{
		return this->ptrData.get();
	}

	const ProjectMeta* ProjectProxy::getMeta() const
	{
		return this->ptrMeta.get();
	}

	const juce::ReadWriteLock& ProjectProxy::getLock() const
	{
		return this->lock;
	}
}