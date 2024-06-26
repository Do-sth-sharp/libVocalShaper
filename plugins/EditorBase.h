﻿#pragma once
#include "../Macros.h"

#include <JuceHeader.h>
#include "Utils.h"
#include "../projects/ProjectProxy.h"

namespace vocalshaper {
	class VSAPI EditorBase : public juce::Component
	{
	public:
		EditorBase();
		virtual ~EditorBase() override;

	protected:
		//添加或移除子编辑器树节点
		void addChildEditor(EditorBase* editor, int zOrder = -1);
		void addChildEditorToDesktop(EditorBase* editor, int flag = 0);
		void addChildEditorAndMakeVisible(EditorBase* editor, int zOrder = -1);
		void removeChildEditor(EditorBase* editor);

	protected:
		//调用此方法获取项目实例
		ProjectProxy* getProject() const;
		//调用此方法获取切换浏览/编辑模式
		bool getEditMode() const;
		//调用此方法获取工具
		uint8_t getToolID() const;
		//调用此方法获取当前轨道
		int getTrackID() const;
		//调用此方法获取当前项目信息锁
		juce::ReadWriteLock& getProjLock() const;
		//调用此方法获取水平浏览范围（针对混合编辑器）
		std::tuple<double, double> getHorizontalViewPort() const;
		//调用此方法获取垂直浏览范围（针对混合编辑器）
		std::tuple<double, double> getVerticalViewPort() const;
		//调用此方法获取水平浏览范围（针对轨道面板）
		std::tuple<double, double> getHViewPort() const;
		//调用此方法获取垂直浏览范围（针对轨道面板）
		std::tuple<double, double> getVViewPort() const;
		//调用此方法获取总长度
		double getTotalLength() const;
		//调用此方法获取当前播放位置
		double getCurrentPosition() const;
		//调用此方法获取播放跟随状态
		double getFollowState() const;
		//调用此方法获取播放循环范围
		std::tuple<double, double> getLoopRange() const;
		//调用此方法获取吸附
		AdsorbState getAdsorb() const;
		//调用此方法获取网格
		GridState getGrid() const;

	protected:
		//当项目实例发生切换时被调用
		virtual void setProjectCallback(const ProjectProxy* ptr);
		//当切换浏览/编辑模式时被调用
		virtual void setEditModeCallback(bool editMode);
		//当切换工具时被调用
		virtual void setToolIDCallback(uint8_t toolID);
		//当切换当前轨道时被调用
		virtual void setTrackIDCallback(int trackID);
		//切换水平浏览范围时被调用（针对混合编辑器）
		virtual void setHorizontalViewPortCallback(double startTime, double endTime);
		//切换垂直浏览范围时被调用（针对混合编辑器）
		virtual void setVerticalViewPortCallback(double bottomPitch, double topPitch);
		//切换水平浏览范围时被调用（针对轨道面板）
		virtual void setHViewPortCallback(double startTime, double endTime);
		//切换垂直浏览范围时被调用（针对轨道面板）
		virtual void setVViewPortCallback(double bottomTrack, double topTrack);
		//更改总长度时被调用
		virtual void setTotalLengthCallback(double totalLength);
		//更改当前播放位置时被调用
		virtual void setCurrentPositionCallback(double currentTime);
		//更改播放跟随状态时被调用
		virtual void setFollowStateCallback(bool follow);
		//更改播放循环范围时被调用
		virtual void setLoopRangeCallback(double startTime, double endTime);
		//更改吸附时被调用
		virtual void setAdsorbCallback(AdsorbState state);
		//更改网格时被调用
		virtual void setGridCallback(GridState state);

	public:
		//当项目实例发生切换时调用
		void setProject(const ProjectProxy* ptr);
		//当切换浏览/编辑模式时调用
		void setEditMode(bool editMode);
		//当切换工具时调用
		void setToolID(uint8_t toolID);
		//当切换当前轨道时调用
		void setTrackID(int trackID);
		//切换水平浏览范围时调用（针对混合编辑器）
		void setHorizontalViewPort(double startTime, double endTime);
		//切换垂直浏览范围时调用（针对混合编辑器）
		void setVerticalViewPort(double bottomPitch, double topPitch);
		//切换水平浏览范围时调用（针对轨道面板）
		void setHViewPort(double startTime, double endTime);
		//切换垂直浏览范围时调用（针对轨道面板）
		void setVViewPort(double bottomTrack, double topTrack);
		//更改总长度时调用
		void setTotalLength(double totalLength);
		//更改当前播放位置时调用
		void setCurrentPosition(double currentTime);
		//更改播放跟随状态时调用
		void setFollowState(bool follow);
		//更改播放循环范围时调用
		void setLoopRange(double startTime, double endTime);
		//更改吸附时调用
		void setAdsorb(AdsorbState state);
		//更改网格时调用
		void setGrid(GridState state);

	public:
		//复制对象时被调用，返回选择对象的拷贝
		virtual void onCopy(SPSList& list);
		//删除对象时被调用
		virtual void onDelete();
		//全选对象时被调用
		virtual void onSelectAll();
		//取消全选对象时被调用
		virtual void onUnselectAll();
		//粘贴对象时被调用
		virtual void onPaste(const SPSList& list);

	public:
		//用于顶层编辑器的导出接口
		virtual void setMethods(
			const std::function<void(int)>& setCurrentTrackFunc,
			const std::function<void(void)>& refreshTotalTimeFunc,
			const std::function<void(double)>& setCurrentPositionFunc,
			const std::function<void(double, double)>& setLoopRangeFunc,
			const std::function<void(double, double)>& setHorizontalViewPortFunc,
			const std::function<void(double, double)>& setVerticalViewPortFunc
		);
		virtual void setTrackViewMethods(
			std::function<void(double, double)> setHViewPortFunc,
			std::function<void(double, double)> setVViewPortFunc
		);

	protected:
		//调用此方法申请更改当前轨道
		void setCurrentTrackMethod(int trackID) const;
		//调用此方法申请刷新轨道总时长显示范围
		void refreshTotalTimeMethod() const;
		//调用此方法申请设置当前播放位置
		void setCurrentPositionMethod(double currentTime) const;
		//调用此方法申请设置循环范围
		void setLoopRangeMethod(double startTime, double endTime) const;
		//调用此方法申请设置水平浏览范围（针对混合编辑器）
		void setHorizontalViewPortMethod(double startTime, double endTime) const;
		//调用此方法申请设置垂直浏览范围（针对混合编辑器）
		void setVerticalViewPortMethod(double bottomPitch, double topPitch) const;
		//调用此方法申请设置水平浏览范围（针对轨道面板）
		void setHViewPortMethod(double startTime, double endTime) const;
		//调用此方法申请设置垂直浏览范围（针对轨道面板）
		void setVViewPortMethod(double bottomTrack, double topTrack) const;

	private:
		//调用此方法更改当前轨道
		std::function<void(int)> setCurrentTrackFunc;
		//调用此方法刷新轨道总时长显示范围
		std::function<void(void)> refreshTotalTimeFunc;
		//调用此方法设置当前播放位置
		std::function<void(double)> setCurrentPositionFunc;
		//调用此方法设置循环范围
		std::function<void(double, double)> setLoopRangeFunc;
		//调用此方法设置水平浏览范围（针对混合编辑器）
		std::function<void(double, double)> setHorizontalViewPortFunc;
		//调用此方法设置水平浏览范围（针对轨道面板）
		std::function<void(double, double)> setHViewPortFunc;
		//调用此方法设置垂直浏览范围（针对混合编辑器）
		std::function<void(double, double)> setVerticalViewPortFunc;
		//调用此方法设置垂直浏览范围（针对轨道面板）
		std::function<void(double, double)> setVViewPortFunc;

	private:
		EditorBase* parentEditor = nullptr;
		juce::Array<EditorBase*> childEditorList;

		bool activeFlag = false;

	private:
		ProjectProxy* project = nullptr;
		int trackID = -1;
		bool editMode = false;
		uint8_t toolID = 1;
		mutable juce::ReadWriteLock projLock;

		double mixStartTime = 0., mixEndTime = 0.;
		double bottomPitch = 0., topPitch = 0.;
		double trackStartTime = 0., trackEndTime = 0.;
		double bottomTrack = 0., topTrack = 0.;

		double totalLength = 0.;
		double currentTime = 0.;
		bool follow = true;
		double loopStartTime = -1., loopEndTime = -1.;

		AdsorbState adsorb = AdsorbState::Adsorb1Beat;
		GridState grid = GridState::Grid1Beat;

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EditorBase)
	};
}