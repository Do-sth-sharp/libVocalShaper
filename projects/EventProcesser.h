#pragma once
#include "../Macros.h"

#include <JuceHeader.h>
#include <stack>
#include "events/ProjectEventStructure.h"

namespace vocalshaper {
	class ProjectProxy;

	class VSAPI EventProcesser : protected juce::Thread
	{
	public:
		EventProcesser() = delete;
		explicit EventProcesser(ProjectProxy* parent);
		~EventProcesser() override;

	public:
		using EventHandleFunc 
			= std::function<void(ProjectEventStructure&, ProjectProxy&)>;

		void processEvent(std::unique_ptr<ProjectEventStructure> event);

		//在使用此方法前请考虑清楚你在做什么
		void setEventHandles(const juce::Array<EventHandleFunc> list);
		
		bool couldUndo() const;
		bool couldRedo() const;
		void undo();
		void redo();

	protected:
		void run() override;

	private:
		juce::CriticalSection queueLock;
		juce::ReadWriteLock recordsLock, handleLock;
		std::queue<std::unique_ptr<ProjectEventStructure>> eventList;
		std::stack<std::unique_ptr<ProjectEventStructure>> stackUndo, stackRedo;
		juce::Array<EventHandleFunc> handleList;

		ProjectProxy* parent = nullptr;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EventProcesser)
	};
}