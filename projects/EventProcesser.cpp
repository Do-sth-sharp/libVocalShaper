#include "EventProcesser.h"

#include "actions/Actions.h"
#include "ProjectProxy.h"
#include "../utils/MemLimit.h"

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
		//触发内存限制，执行被拒绝
		if (!utils::system::MemLimit::sizeIsNotReachedLimit()) {
			//TODO 发送通知
			jassertfalse;
			return;
		}

		//事件入队列
		{
			juce::GenericScopedLock<juce::CriticalSection> locker(this->queueLock);
			this->eventList.push(std::move(event));
		}

		if (!this->isThreadRunning()) {
			this->startThread();
		}
	}

	void EventProcesser::processEvents(juce::OwnedArray<actions::ActionBase>&& events)
	{
		//触发内存限制，执行被拒绝
		if (!utils::system::MemLimit::sizeIsNotReachedLimit()) {
			//TODO 发送通知
			jassertfalse;
			return;
		}

		//事件入队列
		{
			juce::GenericScopedLock<juce::CriticalSection> locker(this->queueLock);
			while (events.size() > 0) {
				this->eventList.push(std::unique_ptr<actions::ActionBase>(events.removeAndReturn(0)));
			}
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

			//触发内存限制，执行被拒绝
			if (!utils::system::MemLimit::sizeIsNotReachedLimit()) {
				//TODO 发送通知
				jassertfalse;
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