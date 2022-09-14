#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "../datas/SerializableProjectStructure.h"

namespace vocalshaper {
	class ProjectProxy;

	class VSAPI ProjectEventStructure
	{
	public:
		enum class Type {
			Empty,		//空
			Project,	//工程
			Track,		//轨道
			MasterTrack,//主轨道
			Note,		//音符
			Phoneme,	//音素
			InstrParam,	//参数值
			NoteParam,	//参数值
			PluginParam,//参数值
			TrackParam,	//参数值
			Point,		//二维点
			Curve,		//曲线段
			DPoint,		//二维导数点
			Script,		//脚本片段
			Wave,		//波形片段
			Plugin,		//音频插件
			Json,		//Json数据
			Label,		//标签
			Instr		//乐器
		};

		Type getType() const;

		enum class ChangeType {
			Add,	//添加
			Edit,	//修改
			Remove	//删除
		};

		ChangeType getChangeType() const;

		void setPtr(SerializableProjectStructure* ptr);

		enum class UndoFlagType {
			Empty,
			Redo,
			Undo
		};

		UndoFlagType getUndoFlag() const;

		using CallBackFunction
			= std::function<void(const ProjectEventStructure&, const ProjectProxy&)>;
		void addCallBack(CallBackFunction callback);

	public:
		ProjectEventStructure(Type type, ChangeType cType);
		virtual ~ProjectEventStructure() = default;

	protected:
		std::unique_ptr<SerializableProjectStructure> ptr;

		virtual void reverse();

	private:
		friend class ProjectMerger;
		friend class EventProcesser;
		friend class EventUndo;

		Type type = Type::Empty;
		ChangeType cType = ChangeType::Add;
		UndoFlagType undoFlag = UndoFlagType::Empty;

		juce::Array<CallBackFunction> callbackList;

		JUCE_LEAK_DETECTOR(ProjectEventStructure)
	};
}