#pragma once
#include "../Macros.h"

#include <JuceHeader.h>
#include "datas/Project.h"
#include "events/Events.h"
#include "ProjectMeta.h"
#include "EventProcesser.h"

namespace vocalshaper {
	class VSAPI ProjectProxy
	{
	public:
		ProjectProxy() = delete;
		ProjectProxy(const juce::String& name, const juce::String& path);
		~ProjectProxy() = default;

	public:
		const juce::String& getName() const;
		const juce::String& getPath() const;

		bool getSaved() const;

		Project* getPtr();
		ProjectMeta* getMeta();
		EventProcesser* getProcesser();

		const juce::ReadWriteLock& getLock() const;

		//销毁当前实例中的项目指针，将ptr中的项目指针移动到当前实例后销毁ptr
		void swallow(ProjectProxy* ptr);

	private:
		friend class EventUndo;

		// name:项目文件名
		// path:项目路径
		const juce::String name;
		const juce::String path;

		std::unique_ptr<Project, std::function<void(Project*)>> ptrData;
		std::unique_ptr<ProjectMeta> ptrMeta;
		std::unique_ptr<EventProcesser> eventProcesser;
		
		juce::ReadWriteLock lock;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ProjectProxy)
	};
}