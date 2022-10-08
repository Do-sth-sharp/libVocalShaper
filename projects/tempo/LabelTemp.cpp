#include "LabelTemp.h"
#include "../ProjectProxy.h"
#include "../datas/Project.h"
#include "../daos/ProjectDAO.h"

#include "../../lua/lua.hpp"
#include "../../utils/IniParser.h"

namespace vocalshaper {
	LabelTemp::LabelTemp(ProjectProxy* parent)
		:parent(parent)
	{}

	void LabelTemp::refresh()
	{
		if (!this->parent) {
			return;
		}

		juce::ScopedWriteLock locker1(this->lock);
		juce::ScopedReadLock locker2(this->parent->getLock());

		auto ptrProject = this->parent->getPtr();
		if (!ptrProject) {
			return;
		}

		//获取标签数量
		int labelSize = ProjectDAO::labelSize(ptrProject);

		//获取量化值
		uint32_t curveQuantification = ProjectDAO::getCurveQuantification(ptrProject);

		//标签状态缓存
		double tempoTemp = 120.0;
		uint8_t beatTemp = 4;

		//如果不存在标签
		if (labelSize <= 0) {
			this->list.add({ 0.0, tempoTemp, beatTemp, false });
		}

		//遍历标签
		for (int i = 0; i < labelSize; i++) {
			auto ptrLabel = ProjectDAO::getLabel(ptrProject, i);
			if (!ptrLabel) {
				continue;
			}

			//如果首个标签不在最开始
			if (i == 0 && timeToDouble(LabelDAO::getPosition(ptrLabel), curveQuantification) > 0) {
				this->list.add({ 0.0, tempoTemp, beatTemp, false });
			}

			//解析标签并放入列表
			LabelData label;
			if (this->parseLabel(ptrLabel, label, curveQuantification, tempoTemp, beatTemp)) {
				this->list.add(label);
			}

			//TODO 标签排序

		}
	}

	bool LabelTemp::parseLabel(
		const Label* label, LabelTemp::LabelData& result, uint32_t curveQ, double& tempoTemp, uint8_t& beatTemp)
	{
		if (!label) {
			return false;
		}

		//判断类型并分别解析
		switch (LabelDAO::getLabelType(label))
		{
		case Label::LabelType::Lua:
			if (!this->parseLuaLabel(LabelDAO::getData(label), result, tempoTemp, beatTemp)) {
				return false;
			}
			break;
		case Label::LabelType::Ini:
			if (!this->parseIniLabel(LabelDAO::getData(label), result, tempoTemp, beatTemp)) {
				return false;
			}
			break;
		case Label::LabelType::Xml:
			if (!this->parseXmlLabel(LabelDAO::getData(label), result, tempoTemp, beatTemp)) {
				return false;
			}
			break;
		case Label::LabelType::Json:
			if (!this->parseJsonLabel(LabelDAO::getData(label), result, tempoTemp, beatTemp)) {
				return false;
			}
			break;
		default:
			return false;
		}

		//设置时间
		result.x = timeToDouble(LabelDAO::getPosition(label), curveQ);
		return true;
	}

	bool LabelTemp::parseLuaLabel(
		const juce::String& data, LabelTemp::LabelData& result, double& tempoTemp, uint8_t& beatTemp)
	{
		//TODO
		/*static std::unique_ptr<lua_State, std::function<void(lua_State*)>> lState
			= std::unique_ptr<lua_State, std::function<void(lua_State*)>>(
				luaL_newstate(), lua_close);*/

		return true;
	}

	bool LabelTemp::parseIniLabel(
		const juce::String& data, LabelTemp::LabelData& result, double& tempoTemp, uint8_t& beatTemp)
	{
		return true;
	}

	bool LabelTemp::parseXmlLabel(
		const juce::String& data, LabelTemp::LabelData& result, double& tempoTemp, uint8_t& beatTemp)
	{
		return true;
	}

	bool LabelTemp::parseJsonLabel(
		const juce::String& data, LabelTemp::LabelData& result, double& tempoTemp, uint8_t& beatTemp)
	{
		return true;
	}
}