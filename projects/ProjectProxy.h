#pragma once
#include "../Macros.h"

#include <JuceHeader.h>
#include "datas/Project.h"
#include "tempo/LabelTemp.h"
#include "tempo/TempoTemp.h"
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
		const TempoTemp* getTempo();

		const juce::ReadWriteLock& getLock() const;

		void changeUrl(const juce::String& name, const juce::String& path);

		//刷新标签和曲速缓存
		void refreshLabels();

	private:
		friend class EventUndo;

		// name:项目文件名
		// path:项目路径
		juce::String name;
		juce::String path;

		std::unique_ptr<Project> ptrData;//单纯工程数据模型
		std::unique_ptr<ProjectMeta> ptrMeta;//工程元数据
		std::unique_ptr<EventProcesser> eventProcesser;//工程事件处理器
		std::unique_ptr<LabelTemp> labelTemp;//标签缓存
		std::unique_ptr<TempoTemp> tempoTemp;//曲速缓存
		
		juce::ReadWriteLock lock;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ProjectProxy)
	};
}