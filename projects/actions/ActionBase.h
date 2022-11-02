#pragma once
#include "../../Macros.h"

#include <JuceHeader.h>
#include "../datas/Project.h"

//移位量
#define VS_ACTION_TYPE_CODE_BIT_MOVE ((sizeof(int) / 2) * 8)

//二级Action类构造参数中与数据更改相关的部分
//用于决定构造的二级Action类构造函数是否具有index参数
//_DataMemType:二级Action类修改的数据类型
#define VS_ACTION_INIT_ARG(_DataMemType) _DataMemType data
#define VS_ACTION_INIT_ARG_WITH_INDEX(_DataMemType) int index, _DataMemType data

//创建二级Action类
//_ActionName:二级Action类名
//_ActionBaseType:继承的一级Action类名
//_DataType:用于储存修改数据的类的类型，在ActionBase类里定义
//_ActionType:二级Action类型，在一级Action类里以枚举的方式定义
//_DataInit:为用于储存修改数据的类中成员以初始化列表形式赋值
//_ArgInit:二级Action类构造参数中与数据更改相关的部分
#define VS_CREATE_ACTION(_ActionName, _ActionBaseType, _DataType, _ActionType, _DataInit, _ArgInit) \
class VSAPI _ActionName : public vocalshaper::actions::_ActionBaseType \
{ \
public: \
	using DataType = vocalshaper::actions::ActionBase::_DataType; \
public: \
	explicit _ActionName(TargetType target, _ArgInit, vocalshaper::ProjectProxy* proxy) \
		:_ActionBaseType(ActionType::Actions::_ActionType, target, new DataType(_DataInit), proxy) {}; \
	virtual ~_ActionName() override = default; \
protected: \
	bool perform() override; \
	bool undo() override; \
private: \
	JUCE_LEAK_DETECTOR(_ActionName) \
};

//为用于储存修改数据的类中成员以初始化列表形式赋值
#define VS_INIT_ROUTINE_DATA data
#define VS_INIT_ROUTINE_DATA_WITH_INDEXED_OBJECT data, index
#define VS_INIT_ROUTINE_DATA_WITH_SINGLE_OBJECT data

//创建进行工程数据属性修改的二级Action
//_ActionName:二级Action类名
//_ActionBaseType:继承的一级Action类名
//_DataType:用于储存修改数据的类的类型，在ActionBase类里定义
//_ActionType:二级Action类型，代表操作的属性或子对象，在一级Action类里以枚举的方式定义
#define VS_CREATE_ROUTINE_ACTION(_ActionName, _ActionBaseType, _DataType, _ActionType) \
VS_CREATE_ACTION(_ActionName, _ActionBaseType, _DataType, _ActionType, VS_INIT_ROUTINE_DATA, VS_ACTION_INIT_ARG(decltype(_DataType::data)))

//创建进行工程结构增删的二级Action
//_ActionName:二级Action类名
//_ActionBaseType:继承的一级Action类名
//_DataMemType:工程结构的类型（应为一个指针）
//_ActionType:二级Action类型，在一级Action类里以枚举的方式定义
#define VS_CREATE_ROUTINE_ACTION_WITH_INDEXED_OBJECT(_ActionName, _ActionBaseType, _DataMemType, _ActionType) \
VS_CREATE_ACTION(_ActionName, _ActionBaseType, IndexObjectData, _ActionType, VS_INIT_ROUTINE_DATA_WITH_INDEXED_OBJECT, VS_ACTION_INIT_ARG_WITH_INDEX(_DataMemType))

//创建进行单一工程结构增删的二级Action
//_ActionName:二级Action类名
//_ActionBaseType:继承的一级Action类名
//_DataMemType:工程结构的类型（应为一个指针）
//_ActionType:二级Action类型，在一级Action类里以枚举的方式定义
#define VS_CREATE_ROUTINE_ACTION_WITH_SINGLE_OBJECT(_ActionName, _ActionBaseType, _DataMemType, _ActionType) \
VS_CREATE_ACTION(_ActionName, _ActionBaseType, ObjectData, _ActionType, VS_INIT_ROUTINE_DATA_WITH_SINGLE_OBJECT, VS_ACTION_INIT_ARG(_DataMemType))

//创建一级Action类
//_ActionBaseType:一级Action类名
//_TargetType:操作目标位置类的类名
//_ActionBaseType:一级Action类型，代表操作的对象类型，在ActionBase类里以枚举的方式定义
//_TargetList:定义操作目标位置类的成员
//_ActionList:定义二级Action类型列表
#define VS_CREATE_ROUTINE_ACTION_BASE(_ActionBaseName, _TargetType, _ActionBaseType, _TargetList, _ActionList) \
class VSAPI _ActionBaseName : public ActionBase \
{ \
public: \
	struct _TargetType : public ActionBase::Target { _TargetList }; \
	enum Actions { \
		Empty = 0x0000, \
		_ActionList \
	}; \
public: \
	using ActionType = _ActionBaseName; \
	using TargetType = _TargetType; \
protected: \
	explicit _ActionBaseName(int action, _TargetType target, ActionBase::Data* data, vocalshaper::ProjectProxy* proxy) \
		:ActionBase(action | (ActionBase::Type::_ActionBaseType << VS_ACTION_TYPE_CODE_BIT_MOVE), \
			new _TargetType(target), data, proxy) {}; \
	virtual bool perform() override { return ActionBase::perform(); }; \
	virtual bool undo() override { return ActionBase::undo(); }; \
public: \
	explicit _ActionBaseName(_TargetType target, vocalshaper::ProjectProxy* proxy) \
		:_ActionBaseName(Actions::Empty, target, nullptr, proxy) {}; \
	virtual ~_ActionBaseName() override = default; \
private: \
	JUCE_LEAK_DETECTOR(_ActionBaseName) \
};

//暴露目标对象
//根据Action数据获取目标对象指针ptrObject并判断是否有效
//_TargetSelectFunc:获取目标对象指针函数，参数1为项目根指针，参数2为操作目标位置类
#define VS_PRAPARE_ROUTINE_DATA_PTR_FROM_ACTION(_TargetSelectFunc) \
auto proxy = this->getProxy(); \
auto data = reinterpret_cast<DataType*>(this->getData()); \
auto target = reinterpret_cast<TargetType*>(this->getTarget()); \
if ((!proxy) || (!data) || (!target)) { \
	return false; \
} \
juce::ScopedWriteLock locker(proxy->getLock()); \
auto ptrObject = _TargetSelectFunc(proxy->getPtr(), target); \
if (!ptrObject) { \
	return false; \
}

//标准属性编辑
//先暴露目标对象，然后对目标对象的属性进行编辑
//_TargetSelectFunc:获取目标对象指针函数，参数1为项目根指针，参数2为操作目标位置类
//_EditDataFunc:编辑目标对象属性函数，参数1为目标对象指针，参数2为新数据的左值引用
//_CurrentFunc:要调用的重写的基类函数
#define VS_EDIT_ROUTINE_DATA_FROM_ACTION(_TargetSelectFunc, _EditDataFunc, _CurrentFunc) \
VS_PRAPARE_ROUTINE_DATA_PTR_FROM_ACTION(_TargetSelectFunc) \
return _EditDataFunc(ptrObject, data->data) && this->ActionType::_CurrentFunc();

//标准子对象增删
//先暴露目标对象，然后对目标对象的子对象进行增删
//_TargetSelectFunc:获取目标对象指针函数，参数1为项目根指针，参数2为操作目标位置类
//_AddOrRemoveDataFunc:增删目标对象子对象函数，参数1为目标对象指针，参数2为目标子对象数据的左值引用（唯一指针的左值引用），参数3为目标子对象在目标对象中的index
//_CurrentFunc:要调用的重写的基类函数
#define VS_ADD_OR_REMOVE_ROUTINE_DATA_FROM_ACTION(_TargetSelectFunc, _AddOrRemoveDataFunc, _CurrentFunc) \
VS_PRAPARE_ROUTINE_DATA_PTR_FROM_ACTION(_TargetSelectFunc) \
return _AddOrRemoveDataFunc(ptrObject, data->data, data->index) && this->ActionType::_CurrentFunc();

//标准单一子对象增删
//先暴露目标对象，然后对目标对象的子对象进行增删
//_TargetSelectFunc:获取目标对象指针函数，参数1为项目根指针，参数2为操作目标位置类
//_AddOrRemoveDataFunc:增删目标对象子对象函数，参数1为目标对象指针，参数2为目标子对象数据的左值引用（唯一指针的左值引用）
//_CurrentFunc:要调用的重写的基类函数
#define VS_ADD_OR_REMOVE_ROUTINE_SINGLE_DATA_FROM_ACTION(_TargetSelectFunc, _AddOrRemoveDataFunc, _CurrentFunc) \
VS_PRAPARE_ROUTINE_DATA_PTR_FROM_ACTION(_TargetSelectFunc) \
return _AddOrRemoveDataFunc(ptrObject, data->data) && this->ActionType::_CurrentFunc();

//创建标准属性编辑方法定义
//_ActionName:二级Action类名
//_TargetSelectFunc:获取目标对象指针函数，参数1为项目根指针，参数2为操作目标位置类
//_EditDataFunc:编辑目标对象属性函数，参数1为目标对象指针，参数2为新数据的左值引用
#define VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(_ActionName, _TargetSelectFunc, _EditDataFunc) \
bool _ActionName::perform() \
{ \
	VS_EDIT_ROUTINE_DATA_FROM_ACTION(_TargetSelectFunc, _EditDataFunc, perform) \
}; \
bool _ActionName::undo() \
{ \
	VS_EDIT_ROUTINE_DATA_FROM_ACTION(_TargetSelectFunc, _EditDataFunc, undo) \
};

//创建标准子对象添加方法定义
//_ActionName:二级Action类名
//_TargetSelectFunc:获取目标对象指针函数，参数1为项目根指针，参数2为操作目标位置类
//_AddDataFunc:增加目标对象子对象函数，参数1为目标对象指针，参数2为目标子对象数据的左值引用（唯一指针的左值引用），参数3为目标子对象在目标对象中的index
//_RemoveDataFunc:删除目标对象子对象函数，参数1为目标对象指针，参数2为目标子对象数据的左值引用（唯一指针的左值引用），参数3为目标子对象在目标对象中的index
#define VS_CREATE_ADD_ROUTINE_DATA_ACTION_DEFINEITION(_ActionName, _TargetSelectFunc, _AddDataFunc, _RemoveDataFunc) \
bool _ActionName::perform() \
{ \
	VS_ADD_OR_REMOVE_ROUTINE_DATA_FROM_ACTION(_TargetSelectFunc, _AddDataFunc, perform) \
}; \
bool _ActionName::undo() \
{ \
	VS_ADD_OR_REMOVE_ROUTINE_DATA_FROM_ACTION(_TargetSelectFunc, _RemoveDataFunc, undo) \
};

//创建标准子对象删除方法定义
//_ActionName:二级Action类名
//_TargetSelectFunc:获取目标对象指针函数，参数1为项目根指针，参数2为操作目标位置类
//_AddDataFunc:增加目标对象子对象函数，参数1为目标对象指针，参数2为目标子对象数据的左值引用（唯一指针的左值引用），参数3为目标子对象在目标对象中的index
//_RemoveDataFunc:删除目标对象子对象函数，参数1为目标对象指针，参数2为目标子对象数据的左值引用（唯一指针的左值引用），参数3为目标子对象在目标对象中的index
#define VS_CREATE_REMOVE_ROUTINE_DATA_ACTION_DEFINEITION(_ActionName, _TargetSelectFunc, _AddDataFunc, _RemoveDataFunc) \
bool _ActionName::perform() \
{ \
	VS_ADD_OR_REMOVE_ROUTINE_DATA_FROM_ACTION(_TargetSelectFunc, _RemoveDataFunc, perform) \
}; \
bool _ActionName::undo() \
{ \
	VS_ADD_OR_REMOVE_ROUTINE_DATA_FROM_ACTION(_TargetSelectFunc, _AddDataFunc, undo) \
};

//创建标准单一子对象添加方法定义
//_ActionName:二级Action类名
//_TargetSelectFunc:获取目标对象指针函数，参数1为项目根指针，参数2为操作目标位置类
//_AddDataFunc:增加目标对象子对象函数，参数1为目标对象指针，参数2为目标子对象数据的左值引用（唯一指针的左值引用）
//_RemoveDataFunc:删除目标对象子对象函数，参数1为目标对象指针，参数2为目标子对象数据的左值引用（唯一指针的左值引用）
#define VS_CREATE_ADD_ROUTINE_SINGLE_DATA_ACTION_DEFINEITION(_ActionName, _TargetSelectFunc, _AddDataFunc, _RemoveDataFunc) \
bool _ActionName::perform() \
{ \
	VS_ADD_OR_REMOVE_ROUTINE_SINGLE_DATA_FROM_ACTION(_TargetSelectFunc, _AddDataFunc, perform) \
}; \
bool _ActionName::undo() \
{ \
	VS_ADD_OR_REMOVE_ROUTINE_SINGLE_DATA_FROM_ACTION(_TargetSelectFunc, _RemoveDataFunc, undo) \
};

//创建标准单一子对象删除方法定义
//_ActionName:二级Action类名
//_TargetSelectFunc:获取目标对象指针函数，参数1为项目根指针，参数2为操作目标位置类
//_AddDataFunc:增加目标对象子对象函数，参数1为目标对象指针，参数2为目标子对象数据的左值引用（唯一指针的左值引用）
//_RemoveDataFunc:删除目标对象子对象函数，参数1为目标对象指针，参数2为目标子对象数据的左值引用（唯一指针的左值引用）
#define VS_CREATE_REMOVE_ROUTINE_SINGLE_DATA_ACTION_DEFINEITION(_ActionName, _TargetSelectFunc, _AddDataFunc, _RemoveDataFunc) \
bool _ActionName::perform() \
{ \
	VS_ADD_OR_REMOVE_ROUTINE_SINGLE_DATA_FROM_ACTION(_TargetSelectFunc, _RemoveDataFunc, perform) \
}; \
bool _ActionName::undo() \
{ \
	VS_ADD_OR_REMOVE_ROUTINE_SINGLE_DATA_FROM_ACTION(_TargetSelectFunc, _AddDataFunc, undo) \
};

//创建标准属性值交换方法
//在对目标属性编辑的同时保存旧的属性值
//_MethodName:方法名称
//_ObjectPtrType:目标对象的类名
//_DataMemType:修改属性的数据类型
//_DAOType:修改目标对象属性使用的DAO类名
//_DAOGetMethodName:DAO类中对应属性的Get方法名
//_DAOSetMethodName:DAO类中对应属性的Set方法名
#define VS_CREATE_ROUTINE_DATA_SWAP_METHOD(_MethodName, _ObjectPtrType, _DataMemType, _DAOType, _DAOGetMethodName, _DAOSetMethodName) \
inline bool _MethodName(vocalshaper::_ObjectPtrType* ptrObject, _DataMemType& data) \
{ \
	if (!ptrObject) { \
		return false; \
	} \
	auto dataTemp = vocalshaper::_DAOType::_DAOGetMethodName(ptrObject); \
	vocalshaper::_DAOType::_DAOSetMethodName(ptrObject, data); \
	data = dataTemp; \
	return true; \
}

//创建标准子对象添加方法
//在合适的位置添加子对象，同时清除子对象的暂存版本
//_MethodName:方法名称
//_ObjectPtrType:目标对象的类名
//_SubObjectPtrType:子对象的类名
//_DAOType:修改目标对象属性使用的DAO类名
//_DAOAddMethodName:DAO类中添加子对象的方法名
#define VS_CREATE_ROUTINE_DATA_ADD_METHOD(_MethodName, _ObjectPtrType, _SubObjectPtrType, _DAOType, _DAOAddMethodName) \
inline bool _MethodName(vocalshaper::_ObjectPtrType* ptrObject, std::unique_ptr<vocalshaper::SerializableProjectStructure>& data, int index) \
{ \
	if (!ptrObject) { \
		return false; \
	} \
	auto ptrData = reinterpret_cast<vocalshaper::_SubObjectPtrType*>(data.release()); \
	if (!vocalshaper::_DAOType::_DAOAddMethodName(ptrObject, index, ptrData)) { \
		data.reset(ptrData); \
	} \
	return true; \
}

//创建标准子对象删除方法
//删除对应的子对象，并将删除的子对象暂存
//_MethodName:方法名称
//_ObjectPtrType:目标对象的类名
//_SubObjectPtrType:子对象的类名
//_DAOType:修改目标对象属性使用的DAO类名
//_DAORemoveMethodName:DAO类中移除子对象的方法名
#define VS_CREATE_ROUTINE_DATA_REMOVE_METHOD(_MethodName, _ObjectPtrType, _SubObjectPtrType, _DAOType, _DAORemoveMethodName) \
inline bool _MethodName(vocalshaper::_ObjectPtrType* ptrObject, std::unique_ptr<vocalshaper::SerializableProjectStructure>& data, int index) \
{ \
	if (!ptrObject) { \
		return false; \
	} \
	data.reset(vocalshaper::_DAOType::_DAORemoveMethodName(ptrObject, index)); \
	return true; \
}

//创建标准单一子对象添加方法
//在合适的位置添加子对象，同时清除子对象的暂存版本
//_MethodName:方法名称
//_ObjectPtrType:目标对象的类名
//_SubObjectPtrType:子对象的类名
//_DAOType:修改目标对象属性使用的DAO类名
//_DAOAddMethodName:DAO类中添加子对象的方法名
#define VS_CREATE_ROUTINE_SINGLE_DATA_ADD_METHOD(_MethodName, _ObjectPtrType, _SubObjectPtrType, _DAOType, _DAOAddMethodName) \
inline bool _MethodName(vocalshaper::_ObjectPtrType* ptrObject, std::unique_ptr<vocalshaper::SerializableProjectStructure>& data) \
{ \
	if (!ptrObject) { \
		return false; \
	} \
	auto ptrData = reinterpret_cast<vocalshaper::_SubObjectPtrType*>(data.release()); \
	if (!vocalshaper::_DAOType::_DAOAddMethodName(ptrObject, ptrData)) { \
		data.reset(ptrData); \
	} \
	return true; \
}

//创建标准单一子对象删除方法
//删除对应的子对象，并将删除的子对象暂存
//_MethodName:方法名称
//_ObjectPtrType:目标对象的类名
//_SubObjectPtrType:子对象的类名
//_DAOType:修改目标对象属性使用的DAO类名
//_DAORemoveMethodName:DAO类中移除子对象的方法名
#define VS_CREATE_ROUTINE_SINGLE_DATA_REMOVE_METHOD(_MethodName, _ObjectPtrType, _SubObjectPtrType, _DAOType, _DAORemoveMethodName) \
inline bool _MethodName(vocalshaper::_ObjectPtrType* ptrObject, std::unique_ptr<vocalshaper::SerializableProjectStructure>& data) \
{ \
	if (!ptrObject) { \
		return false; \
	} \
	data.reset(vocalshaper::_DAOType::_DAORemoveMethodName(ptrObject)); \
	return true; \
}

//创建获取目标对象指针方法
//_MethodName:方法名称
//_ObjectPtrType:目标对象的类名
//_ActionBaseType:一级Action的类名
//_SelectObject:获取目标对象指针的代码段，由Project指针ptr和目标对象位置target指针返回目标对象的指针
#define VS_CREATE_OBJECT_SELECT_METHOD_BY_ACTION(_MethodName, _ObjectPtrType, _ActionBaseType, _SelectObject) \
inline vocalshaper::_ObjectPtrType* _MethodName(vocalshaper::Project* ptr, vocalshaper::actions::_ActionBaseType::TargetType* target) \
{ \
	if ((!ptr) || (!target)) { \
		return nullptr; \
	} \
	return _SelectObject; \
}

//用于储存修改数据的类，不含index
//_TypeName:储存修改数据的类的类名
//_MemType:修改数据的数据类型
//_DefaultValue:修改数据的默认值
#define VS_CREATE_ACTION_DATA_TYPE(_TypeName, _MemType, _DefaultValue) \
struct _TypeName : public Data { _MemType data = _DefaultValue; _TypeName() = default; _TypeName(_MemType data) : data(data) {}; private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(_TypeName) };

//用于储存修改数据的类，带index
//_TypeName:储存修改数据的类的类名
//_MemType:修改数据的数据类型
//_DefaultValue:修改数据的默认值
#define VS_CREATE_ACTION_DATA_TYPE_WITH_INDEX(_TypeName, _MemType, _DefaultValue) \
struct _TypeName : public Data { _MemType data = _DefaultValue; int index = 0; _TypeName() = default; _TypeName(_MemType data, int index) : data(data), index(index) {}; private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(_TypeName) };

//用于储存修改对象的类，不含index
//_TypeName:储存修改数据的类的类名
//_MemType:修改数据的数据类型
//_DefaultValue:修改数据的默认值
#define VS_CREATE_ACTION_OBJECT_DATA_TYPE(_TypeName, _MemType) \
struct _TypeName : public Data { std::unique_ptr<_MemType> data = nullptr; _TypeName() = default; _TypeName(_MemType* data) : data(data) {}; private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(_TypeName) };

//用于储存修改对象的类，带index
//_TypeName:储存修改数据的类的类名
//_MemType:修改数据的数据类型
//_DefaultValue:修改数据的默认值
#define VS_CREATE_ACTION_OBJECT_DATA_TYPE_WITH_INDEX(_TypeName, _MemType) \
struct _TypeName : public Data { std::unique_ptr<_MemType> data = nullptr; int index = 0; _TypeName() = default; _TypeName(_MemType* data, int index) : data(data), index(index) {}; private: JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(_TypeName) };

namespace vocalshaper {
	class VSAPI ProjectProxy;

	namespace actions {
		class VSAPI ActionBase : public juce::UndoableAction
		{
		public:
			enum Type {
				Empty = 0x0000,		//空
				Project,			//工程
				Track,				//轨道
				Label,				//标签
				Script,				//脚本片段
				Json,				//Json数据
				Curve,				//曲线段
				Plugin,				//音频插件
				Note,				//音符
				Instr,				//乐器
				Wave,				//波形片段
				TrackParam,			//参数值
				DPoint,				//二维导数点
				PluginParam,		//参数值
				Phoneme,			//音素
				NoteParam,			//参数值
				InstrParam,			//参数值
				Point				//二维点
			};

			struct Target {};
			struct Data {
				Data() = default;
				virtual ~Data() = default;

			private:
				JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Data)
			};

			VS_CREATE_ACTION_DATA_TYPE(BoolData, bool, false);
			VS_CREATE_ACTION_DATA_TYPE(IntData, int, 0);
			VS_CREATE_ACTION_DATA_TYPE(Int8Data, int8_t, 0);
			VS_CREATE_ACTION_DATA_TYPE(UInt8Data, uint8_t, 0);
			VS_CREATE_ACTION_DATA_TYPE(Int16Data, int16_t, 0);
			VS_CREATE_ACTION_DATA_TYPE(UInt16Data, uint16_t, 0);
			VS_CREATE_ACTION_DATA_TYPE(Int32Data, int32_t, 0);
			VS_CREATE_ACTION_DATA_TYPE(UInt32Data, uint32_t, 0);
			VS_CREATE_ACTION_DATA_TYPE(Int64Data, int64_t, 0);
			VS_CREATE_ACTION_DATA_TYPE(UInt64Data, uint64_t, 0);
			VS_CREATE_ACTION_DATA_TYPE(DoubleData, double, 0.);
			VS_CREATE_ACTION_DATA_TYPE(FloatData, float, 0.f);
			VS_CREATE_ACTION_DATA_TYPE(StringData, juce::String, juce::String());
			VS_CREATE_ACTION_DATA_TYPE(ColorData, juce::Colour, juce::Colour());
			VS_CREATE_ACTION_OBJECT_DATA_TYPE(ObjectData, vocalshaper::SerializableProjectStructure);
			VS_CREATE_ACTION_OBJECT_DATA_TYPE_WITH_INDEX(IndexObjectData, vocalshaper::SerializableProjectStructure);

			VS_CREATE_ACTION_DATA_TYPE(LabelTypeData, vocalshaper::Label::LabelType, vocalshaper::Label::LabelType::Lua);
			VS_CREATE_ACTION_DATA_TYPE(ScriptTypeData, vocalshaper::Script::ScriptType, vocalshaper::Script::ScriptType::Lua);

			enum class UndoType
			{
				Perform,
				Undo
			};
			using RuleFunc = std::function<void(const ActionBase&, UndoType)>;
			using CallBackFunc = std::function<void(const ActionBase&, UndoType)>;
		public:
			int getType() const { return this->type; };
			int getBaseType() const { return (this->type >> VS_ACTION_TYPE_CODE_BIT_MOVE); };
			int getActionType() const { return ((this->type << VS_ACTION_TYPE_CODE_BIT_MOVE) >> VS_ACTION_TYPE_CODE_BIT_MOVE); };
			Target* getTarget() const { return this->ptrTarget.get(); };
			Data* getData() const { return this->ptrData.get(); };
			ProjectProxy* getProxy() const { return this->proxy; };

			//关于规则和回调的区别
			//规则会先于回调执行
			//故建议利用规则更新数据缓存，利用回调更新界面

			void addRule(const RuleFunc& rule)
			{ 
				juce::ScopedWriteLock locker(this->ruleLock);
				this->rules.add(rule); 
			};
			void addCallBack(const CallBackFunc& callBack)
			{
				juce::ScopedWriteLock locker(this->callBackLock);
				this->callBacks.add(callBack);
			};

			void run()
			{
				this->perform();
			};
		protected:
			//type:操作对象类型
			//target:操作目标位置
			//data:操作数据
			//proxy:工程管理器
			explicit ActionBase(int type, Target* target, Data* data, vocalshaper::ProjectProxy* proxy)
				:type(type), ptrTarget(target), ptrData(data), proxy(proxy) {};

			//执行更改与撤销更改
			virtual bool perform() override
			{
				//执行规则
				{
					juce::ScopedReadLock locker(this->ruleLock);
					for (auto& f : this->rules) {
						f(*this, UndoType::Perform);
					}
				}
				
				//调用回调
				{
					juce::ScopedReadLock locker(this->callBackLock);
					for (auto& f : this->callBacks) {
						f(*this, UndoType::Perform);
					}
				}

				return true;
			};

			virtual bool undo() override
			{
				//执行规则
				{
					juce::ScopedReadLock locker(this->ruleLock);
					for (auto& f : this->rules) {
						f(*this, UndoType::Undo);
					}
				}

				//调用回调
				{
					juce::ScopedReadLock locker(this->callBackLock);
					for (auto& f : this->callBacks) {
						f(*this, UndoType::Undo);
					}
				}

				return true;
			};

			//数据占内存空间大小的权重
			virtual int getSizeInUnits() override { return 10; };

		public:
			virtual ~ActionBase() override = default;

		private:
			//type规则：前两字节对象类型代码，后两字节操作代码
			int type = 0x0 | (Type::Empty << VS_ACTION_TYPE_CODE_BIT_MOVE);	//修改目标的类型
			std::unique_ptr<Target> ptrTarget = nullptr;	//目标位置
			std::unique_ptr<Data> ptrData = nullptr;		//数据储存
			vocalshaper::ProjectProxy* proxy = nullptr;		//目标项目
			juce::Array<RuleFunc> rules;					//处理规则
			juce::Array<CallBackFunc> callBacks;			//回调函数
			juce::ReadWriteLock ruleLock, callBackLock;		//读写锁

			JUCE_LEAK_DETECTOR(ActionBase)
		};
	}
}