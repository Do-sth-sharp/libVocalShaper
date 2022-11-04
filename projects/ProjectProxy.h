#pragma once
#include "../Macros.h"

#include <JuceHeader.h>
#include "datas/Project.h"
#include "tempo/LabelTemp.h"
#include "tempo/TempoTemp.h"
#include "tempo/BeatTemp.h"
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
		using SaveCallbackFunc = std::function<void(const ProjectProxy*)>;
		using CloseCallbackFunc= std::function<void(const ProjectProxy*)>;

		//这是提供给插件模块使用的回调管理方法
		//在使用此方法前请考虑清楚你在做什么
		void addSaveCallbacks(const juce::Array<SaveCallbackFunc> list);
		//这是提供给插件模块使用的回调管理方法
		//在使用此方法前请考虑清楚你在做什么
		void clearSaveCallbacks();
		//这是提供给插件模块使用的回调管理方法
		//在使用此方法前请考虑清楚你在做什么
		void addCloseCallbacks(const juce::Array<CloseCallbackFunc> list);
		//这是提供给插件模块使用的回调管理方法
		//在使用此方法前请考虑清楚你在做什么
		void clearCloseCallbacks();

		//执行保存回调
		void noticeSave();
		//执行关闭回调
		void noticeClose();

		const juce::String& getName() const;
		const juce::String& getPath() const;

		bool getSaved() const;

		Project* getPtr();
		ProjectMeta* getMeta();
		EventProcesser* getProcesser();
		const LabelTemp* getLabelParser();
		const TempoTemp* getTempo();
		const BeatTemp* getBeat();

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

		std::unique_ptr<Project> ptrData;				//单纯工程数据模型
		std::unique_ptr<ProjectMeta> ptrMeta;			//工程元数据
		std::unique_ptr<EventProcesser> eventProcesser;	//工程事件处理器
		std::unique_ptr<LabelTemp> labelTemp;			//标签缓存
		std::unique_ptr<TempoTemp> tempoTemp;			//曲速缓存
		std::unique_ptr<BeatTemp> beatTemp;				//节拍缓存
		
		juce::ReadWriteLock lock;
		juce::ReadWriteLock callbackLock;				//回调列表锁

		juce::Array<SaveCallbackFunc> saveCallbackList;		//保存回调列表
		juce::Array<CloseCallbackFunc> closeCallbackList;	//关闭回调列表

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ProjectProxy)
	};
}