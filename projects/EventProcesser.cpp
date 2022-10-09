#include "EventProcesser.h"

#include "EventUndo.h"

namespace vocalshaper {
	EventProcesser::EventProcesser(ProjectProxy* parent)
		:Thread("VocalShaper Project Event Processer"),
		parent(parent)
	{}

	EventProcesser::~EventProcesser()
	{
		if (this->isThreadRunning()) {
			this->stopThread(5000);
		}
	}

	void EventProcesser::processEvent(std::unique_ptr<ProjectEventStructure> event)
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

	void EventProcesser::setEventHandles(const juce::Array<EventHandleFunc> list)
	{
		juce::ScopedWriteLock locker(this->handleLock);
		this->handleList.clear();
		this->handleList.addArray(list);
	}

	void EventProcesser::run()
	{
		std::unique_ptr<ProjectEventStructure> event = nullptr;

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

			//处理事件
			{
				juce::ScopedReadLock locker(this->handleLock);
				for (auto& f : this->handleList) {
					//判断停止
					if (this->threadShouldExit()) {
						return;
					}

					//调用
					f(*event, *this->parent);
				}
			}

			//执行回调
			for (auto& f : event->callbackList) {
				f(*event, *this->parent);
			}

			//事件入库
			{
				juce::ScopedWriteLock locker(this->recordsLock);
				switch (event->undoFlag)
				{
				case ProjectEventStructure::UndoFlagType::Empty:
					while (this->stackRedo.size() > 0) {
						this->stackRedo.pop();
					}
					if (event->ptr || event->cType == ProjectEventStructure::ChangeType::Add) {
						this->stackUndo.push(std::move(event));
					}
					break;
				case ProjectEventStructure::UndoFlagType::Undo:
					this->stackRedo.push(std::move(event));
					break;
				case ProjectEventStructure::UndoFlagType::Redo:
					this->stackUndo.push(std::move(event));
					break;
				}
			}
		}
	}

	bool EventProcesser::couldUndo() const
	{
		juce::ScopedReadLock locker(this->recordsLock);
		return this->stackUndo.size() > 0;
	}

	bool EventProcesser::couldRedo() const
	{
		juce::ScopedReadLock locker(this->recordsLock);
		return this->stackRedo.size() > 0;
	}

	void EventProcesser::undo()
	{
		juce::ScopedWriteLock locker(this->recordsLock);
		if (this->stackUndo.size() == 0) {
			return;
		}

		std::unique_ptr<ProjectEventStructure> event = std::move(this->stackUndo.top());
		this->stackUndo.pop();

		event->reverse();
		EventUndo::undo(event.get(), this->parent);

		this->processEvent(std::move(event));
	}

	void EventProcesser::redo()
	{
		juce::ScopedWriteLock locker(this->recordsLock);
		if (this->stackRedo.size() == 0) {
			return;
		}

		std::unique_ptr<ProjectEventStructure> event = std::move(this->stackRedo.top());
		this->stackRedo.pop();

		event->reverse();
		EventUndo::undo(event.get(), this->parent);

		this->processEvent(std::move(event));
	}
}