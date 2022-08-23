#pragma once
#include "../Macros.h"

#include <JuceHeader.h>

namespace vocalshaper {
	//SerializableProjectStructure是VocalShaper中所有工程相关的结构的共同基类
	class VSAPI SerializableProjectStructure
	{
	public:
		enum class Type {
			Empty,	//空
			Project,//工程
			Track,	//轨道
			Note,	//音符
			Param,	//参数值
			Point,	//二维点
			Curve,	//曲线段
			DPoint,	//二维导数点
			Script,	//脚本片段
			Wave,	//波形片段
			Plugin,	//音频插件
			Json,	//Json数据
			Label,	//标签
			Instr	//乐器
		};

		Type getType() const;

	public:
		SerializableProjectStructure(Type type);
		virtual ~SerializableProjectStructure() = default;

	private:
		Type type = Type::Empty;
	};
}
