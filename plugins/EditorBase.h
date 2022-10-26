#pragma once
#include "../Macros.h"

#include <JuceHeader.h>
#include "../projects/datas/Utils.h"
#include "Utils.h"

namespace vocalshaper {
	class VSAPI ProjectProxy;
	class VSAPI SerializableProjectStructure;

	class VSAPI EditorBase : public juce::Component
	{
	public:
		EditorBase();
		virtual ~EditorBase() override = default;

	public:
		//当项目实例发生切换时被调用
		virtual void projectChanged(const ProjectProxy* ptr);
		//当切换浏览/编辑模式时被调用
		virtual void setEditMode(bool editMode);
		//当切换工具时被调用
		virtual void setToolID(uint8_t toolID);
		//当切换当前轨道时被调用
		virtual void trackChanged(int trackID);
		//切换水平浏览范围时被调用（针对混合编辑器）
		virtual void setHorizontalViewPort(ProjectTime startTime, ProjectTime endTime);
		//切换垂直浏览范围时被调用（针对混合编辑器）
		virtual void setVerticalViewPort(double bottomPitch, double topPitch);
		//切换水平浏览范围时被调用（针对轨道面板）
		virtual void setHViewPort(ProjectTime startTime, ProjectTime endTime);
		//切换垂直浏览范围时被调用（针对轨道面板）
		virtual void setVViewPort(double bottomTrack, double topTrack);
		//更改总长度时被调用
		virtual void setTotalLength(ProjectTime totalLength);
		//更改当前播放位置时被调用
		virtual void setCurrentPosition(ProjectTime currentTime);
		//更改播放跟随状态时被调用
		virtual void setFollowState(bool follow);
		//更改播放循环范围时被调用
		virtual void setLoopRange(ProjectTime startTime, ProjectTime endTime);
		//更改吸附时被调用
		virtual void setAdsorb(AdsorbState state);
		//更改网格时被调用
		virtual void setGrid(GridState state);

		//判断当前编辑器是否具有可编辑的焦点
		//可编辑焦点指：
		//1.焦点在当前编辑器内
		//2.焦点所在目标可以进行复制、剪切、删除、选择操作
		virtual bool isActive();
		//获取当前焦点所在目标的副本
		virtual juce::OwnedArray<SerializableProjectStructure> getCopy();
		//获取当前焦点所在目标的副本并移除对象
		virtual juce::OwnedArray<SerializableProjectStructure> getCut();
		//移除当前焦点所在目标
		virtual bool wannaDelete();
		//创建当前焦点所在目标的一份副本
		virtual bool wannaCopy();
		//全选对象
		virtual bool wannaSelectAll();
		//粘贴对象到播放指针位置
		virtual bool wannaPaste(juce::OwnedArray<SerializableProjectStructure> list);
		//粘贴对象到播放指针位置（json对象格式）
		virtual bool wannaPaste(const juce::StringArray& list);
		//显示剪贴板并返回选择的对象
		virtual int showClipBoard(const juce::StringArray& list);

	public:
		virtual void setMethods(
			const std::function<void(int)>& setCurrentTrackFunc,
			const std::function<void(void)>& refreshTotalTimeFunc,
			const std::function<void(ProjectTime)>& setCurrentPositionFunc,
			const std::function<void(ProjectTime, ProjectTime)>& setLoopRangeFunc,
			const std::function<void(ProjectTime, ProjectTime)>& setHorizontalViewPortFunc,
			const std::function<void(double, double)>& setVerticalViewPortFunc
		);
		virtual void setTrackViewMethods(
			std::function<void(ProjectTime, ProjectTime)> setHViewPortFunc,
			std::function<void(double, double)> setVViewPortFunc
		);

	protected:
		//调用此方法申请更改当前轨道
		void setCurrentTrackMethod(int trackID) const;
		//调用此方法申请刷新轨道总时长显示范围
		void refreshTotalTimeMethod() const;
		//调用此方法申请设置当前播放位置
		void setCurrentPositionMethod(ProjectTime currentTime) const;
		//调用此方法申请设置循环范围
		void setLoopRangeMethod(ProjectTime startTime, ProjectTime endTime) const;
		//调用此方法申请设置水平浏览范围（针对混合编辑器）
		void setHorizontalViewPortMethod(ProjectTime startTime, ProjectTime endTime) const;
		//调用此方法申请设置垂直浏览范围（针对混合编辑器）
		void setVerticalViewPortMethod(double bottomPitch, double topPitch) const;
		//调用此方法申请设置水平浏览范围（针对轨道面板）
		void setHViewPortMethod(ProjectTime startTime, ProjectTime endTime) const;
		//调用此方法申请设置垂直浏览范围（针对轨道面板）
		void setVViewPortMethod(double bottomTrack, double topTrack) const;

	private:
		//调用此方法更改当前轨道
		std::function<void(int)> setCurrentTrackFunc;
		//调用此方法刷新轨道总时长显示范围
		std::function<void(void)> refreshTotalTimeFunc;
		//调用此方法设置当前播放位置
		std::function<void(ProjectTime)> setCurrentPositionFunc;
		//调用此方法设置循环范围
		std::function<void(ProjectTime, ProjectTime)> setLoopRangeFunc;
		//调用此方法设置水平浏览范围（针对混合编辑器）
		std::function<void(ProjectTime, ProjectTime)> setHorizontalViewPortFunc;
		//调用此方法设置水平浏览范围（针对轨道面板）
		std::function<void(ProjectTime, ProjectTime)> setHViewPortFunc;
		//调用此方法设置垂直浏览范围（针对混合编辑器）
		std::function<void(double, double)> setVerticalViewPortFunc;
		//调用此方法设置垂直浏览范围（针对轨道面板）
		std::function<void(double, double)> setVViewPortFunc;

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EditorBase)
	};
}