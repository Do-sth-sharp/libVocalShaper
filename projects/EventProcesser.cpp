#include "EventProcesser.h"

#include "actions/Actions.h"
#include "ProjectProxy.h"

namespace vocalshaper {
	EventProcesser::EventProcesser()
		:Thread("VocalShaper Project Event Processer")
	{}

	EventProcesser::~EventProcesser()
	{
		if (this->isThreadRunning()) {
			this->stopThread(5000);
		}
	}

	void EventProcesser::processEvent(std::unique_ptr<actions::ActionBase> event)
	{
		//事件入队列
		{
			juce::GenericScopedLock<juce::CriticalSection> locker(this->queueLock);
			this->eventList.push(std::move(event));
		}

		if (!this->isThreadRunning()) {
			this->startThread();
		}
	}

	void EventProcesser::addEventHandles(const juce::Array<EventHandleFunc> list)
	{
		juce::ScopedWriteLock locker(this->handleLock);
		this->handleList.addArray(list);
	}

	void EventProcesser::clearEventHandles()
	{
		juce::ScopedWriteLock locker(this->handleLock);
		this->handleList.clear();
	}

	void EventProcesser::addEventRules(const juce::Array<actions::ActionBase::RuleFunc> list)
	{
		juce::ScopedWriteLock locker(this->ruleLock);
		this->ruleList.addArray(list);
	}

	void EventProcesser::run()
	{
		std::unique_ptr<actions::ActionBase> event = nullptr;

		while (true) {
			//判断停止
			if (this->threadShouldExit()) {
				return;
			}

			//获取event
			{
				juce::GenericScopedLock<juce::CriticalSection> locker(this->queueLock);
				if (this->eventList.empty()) {
					break;
				}
				event = std::move(this->eventList.front());
				this->eventList.pop();
			}

			//给event添加规则
			{
				this->addRulesOnAction(event.get());
			}

			//插件加工event
			{
				juce::ScopedReadLock locker(this->handleLock);
				for (auto& f : this->handleList) {
					//判断停止
					if (this->threadShouldExit()) {
						return;
					}

					//调用
					f(*event);
				}
			}

			//执行event
			{
				if (event->getActionType() != 0x0000) {
					//实际修改，可撤销
					this->undoManager.perform(event.release());
				}
				else {
					//非实际修改，不可撤销
					event->run();
				}
				
			}
		}
	}

	bool EventProcesser::couldUndo() const
	{
		return this->undoManager.canUndo();
	}

	bool EventProcesser::couldRedo() const
	{
		return this->undoManager.canRedo();
	}

	void EventProcesser::undo()
	{
		this->undoManager.undo();
	}

	void EventProcesser::redo()
	{
		this->undoManager.redo();
	}

	void EventProcesser::addRulesOnAction(actions::ActionBase* action) const
	{
		juce::ScopedReadLock locker(this->ruleLock);
		for (auto &f : this->ruleList) {
			action->addRule(f);
		}
	}
}