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

	const juce::ReadWriteLock& ProjectProxy::getLock() const
	{
		return this->lock;
	}

	void ProjectProxy::swallow(ProjectProxy* ptr)
	{
		if (this == ptr) {
			jassertfalse;
			return;
		}

		juce::ScopedWriteLock locker1(this->getLock());
		juce::ScopedWriteLock locker2(ptr->getLock());

		//TODO 在此处增加对应的移动
		this->ptrData.reset(ptr->ptrData.release());
		this->ptrMeta.reset(ptr->ptrMeta.release());
		this->eventProcesser.reset(ptr->eventProcesser.release());
		this->labelTemp.reset(ptr->labelTemp.release());

		delete ptr;
		ptr = nullptr;
	}
}