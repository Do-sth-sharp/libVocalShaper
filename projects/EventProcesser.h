#pragma once
#include "../Macros.h"

#include <JuceHeader.h>
#include "actions/ActionBase.h"

namespace vocalshaper {
	class ProjectProxy;

	class VSAPI EventProcesser : protected juce::Thread
	{
	public:
		EventProcesser();
		~EventProcesser() override;

	public:
		using EventHandleFunc 
			= std::function<void(actions::ActionBase&)>;

		void processEvent(std::unique_ptr<actions::ActionBase> event);
		void processEvents(juce::OwnedArray<actions::ActionBase>&& events);

		//这是提供给插件模块使用的回调管理方法
		//在使用此方法前请考虑清楚你在做什么
		void addEventHandles(const juce::Array<EventHandleFunc> list);
		//这是提供给插件模块使用的回调管理方法
		//在使用此方法前请考虑清楚你在做什么
		void clearEventHandles();

		void addEventRules(const juce::Array<actions::ActionBase::RuleFunc> list);
		
		bool couldUndo() const;
		bool couldRedo() const;
		void undo();
		void redo();

	protected:
		void run() override;

	private:
		juce::CriticalSection queueLock;							//事件队列锁
		juce::ReadWriteLock handleLock;								//加工器列表锁
		juce::ReadWriteLock ruleLock;								//规则列表锁

		std::queue<std::unique_ptr<actions::ActionBase>> eventList;	//事件队列
		juce::UndoManager undoManager;								//执行器、重做列表
		juce::Array<EventHandleFunc> handleList;					//加工器列表
		juce::Array<actions::ActionBase::RuleFunc> ruleList;		//规则列表

		void addRulesOnAction(actions::ActionBase* action) const;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EventProcesser)
	};
}