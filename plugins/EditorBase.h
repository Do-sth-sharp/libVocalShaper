#pragma once
#include "../Macros.h"

#include <JuceHeader.h>

namespace vocalshaper {
	class VSAPI ProjectProxy;
	class VSAPI SerializableProjectStructure;

	class VSAPI EditorBase : public juce::Component
	{
	public:
		EditorBase();
		virtual ~EditorBase() override = default;

	public:
		//当项目实例发生切换时调用
		virtual void projectChanged(const vocalshaper::ProjectProxy* ptr);
		//当切换浏览/编辑模式时调用
		virtual void setEditMode(bool editMode);
		//当切换工具时调用
		virtual void setToolID(uint8_t toolID);
		//当切换当前轨道时调用
		virtual void trackChanged(int trackID);

		//判断当前编辑器是否具有可编辑的焦点
		//可编辑焦点指：
		//1.焦点在当前编辑器内
		//2.焦点所在目标可以进行复制、剪切、删除、选择操作
		virtual bool isActive();
		//获取当前焦点所在目标的副本
		virtual juce::OwnedArray<vocalshaper::SerializableProjectStructure> getCopy();
		//获取当前焦点所在目标的副本并移除对象
		virtual juce::OwnedArray<vocalshaper::SerializableProjectStructure> getCut();
		//移除当前焦点所在目标
		virtual bool wannaDelete();
		//创建当前焦点所在目标的一份副本
		virtual bool wannaCopy();
		//全选对象
		virtual bool wannaSelectAll();
		//粘贴对象到播放指针位置
		virtual bool wannaPaste(juce::OwnedArray<vocalshaper::SerializableProjectStructure> list);
		//粘贴对象到播放指针位置（json对象格式）
		virtual bool wannaPaste(const juce::StringArray& list);
		//显示剪贴板并返回选择的对象
		virtual int showClipBoard(const juce::StringArray& list);

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EditorBase)
	};
}