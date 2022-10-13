#include "ProjectProxy.h"
#include "daos/ProjectDAO.h"

namespace vocalshaper {
	ProjectProxy::ProjectProxy(const juce::String& name, const juce::String& path)
		:name(name), path(path)
	{
		//初始化结构
		this->ptrData = std::make_unique<Project>();
		this->ptrMeta = std::make_unique<ProjectMeta>();
		this->eventProcesser = std::make_unique<EventProcesser>();
		this->labelTemp = std::make_unique<LabelTemp>(this);
		this->tempoTemp = std::make_unique<TempoTemp>(this->labelTemp.get());

		//添加规则
		this->eventProcesser->addEventRules({
			[](const actions::ActionBase& action, actions::ActionBase::UndoType type) {
				//标签刷新
				if (action.getBaseType() == actions::ActionBase::Type::Project ||
					action.getBaseType() == actions::ActionBase::Type::Label
					) {
					auto proxy = action.getProxy();
					proxy->refreshLabels();
				}
			}
			});
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