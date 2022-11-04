#include "LabelTemp.h"
#include "../ProjectProxy.h"
#include "../datas/Project.h"
#include "../daos/ProjectDAO.h"

#include "../../lua/lua.hpp"
#include "../../utils/IniParser.h"

namespace vocalshaper {
	LabelTemp::LabelTemp(ProjectProxy* parent)
		:parent(parent), luaState(
			std::unique_ptr<lua_State, std::function<void(lua_State*)>>(
			luaL_newstate(), lua_close))
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

		//清空标签缓存
		this->list.clear();

		//获取标签数量
		int labelSize = ProjectDAO::labelSize(ptrProject);

		//标签状态缓存
		double tempoTemp = 120.0;
		uint8_t beatTemp = 4;

		//默认标签
		this->list.add({ 0.0, tempoTemp, beatTemp, false });

		//遍历标签
		for (int i = 0; i < labelSize; i++) {
			auto ptrLabel = ProjectDAO::getLabel(ptrProject, i);
			if (!ptrLabel) {
				continue;
			}

			//解析标签并放入列表
			{
				LabelData label;
				if (this->parseLabel(ptrLabel, label, tempoTemp, beatTemp)) {
					//合法检查
					if (label.beat <= 0 || label.beat > 20) { beatTemp = label.beat = 4; }
					if (label.tempo <= 0. || label.tempo > 500.) { tempoTemp = label.tempo = 120.; }

					//防重叠写入
					if (label.x > this->list.getLast().x) {
						this->list.add(label);
					}
					else if (label.x == this->list.getLast().x) {
						this->list.getReference(this->list.size() - 1) = label;
					}
				}
			}
		}
	}

	bool LabelTemp::parseNow(
		const juce::String& data, LabelData& result, Label::LabelType type,
		double x, double tempoTemp, uint8_t beatTemp) const
	{
		//判断类型并分别解析
		switch (type)
		{
		case Label::LabelType::Lua:
			return this->parseLuaLabel(data, result, x, tempoTemp, beatTemp);
		case Label::LabelType::Ini:
			return this->parseIniLabel(data, result, x, tempoTemp, beatTemp);
		case Label::LabelType::Xml:
			return this->parseXmlLabel(data, result, x, tempoTemp, beatTemp);
		case Label::LabelType::Json:
			return this->parseJsonLabel(data, result, x, tempoTemp, beatTemp);
		default:
			return false;
		}
	}

	bool LabelTemp::parseLabel(
		const Label* label, LabelTemp::LabelData& result, double& tempoTemp, uint8_t& beatTemp) const
	{
		if (!label) {
			return false;
		}

		//设置时间
		result.x = LabelDAO::getPosition(label);

		//判断类型并分别解析
		switch (LabelDAO::getLabelType(label))
		{
		case Label::LabelType::Lua:
			if (!this->parseLuaLabel(LabelDAO::getData(label), result, result.x, tempoTemp, beatTemp)) {
				return false;
			}
			break;
		case Label::LabelType::Ini:
			if (!this->parseIniLabel(LabelDAO::getData(label), result, result.x, tempoTemp, beatTemp)) {
				return false;
			}
			break;
		case Label::LabelType::Xml:
			if (!this->parseXmlLabel(LabelDAO::getData(label), result, result.x, tempoTemp, beatTemp)) {
				return false;
			}
			break;
		case Label::LabelType::Json:
			if (!this->parseJsonLabel(LabelDAO::getData(label), result, result.x, tempoTemp, beatTemp)) {
				return false;
			}
			break;
		default:
			return false;
		}

		return true;
	}

	class LuaGuard final : public juce::Thread
	{
	public:
		explicit LuaGuard(lua_State* state, int timeOut = 3000)
			:Thread("Lua Guard Thread"),
			state(state), timeOut(timeOut)
		{};
		~LuaGuard() override
		{
			if (this->isThreadRunning()) {
				this->stopThread(this->timeOut);
			}
		};

	private:
		static void timeOutBreakHook(lua_State* L, lua_Debug* /*d*/)
		{
			lua_sethook(L, NULL, 0, 0);
			luaL_error(L, "@LabelParser:Script Timeout!");
		};

	public:
		void run() override
		{
			auto startTime = juce::Time::currentTimeMillis();
			auto currentTime = startTime;

			while (!this->threadShouldExit()) {
				currentTime = juce::Time::currentTimeMillis();

				if (currentTime - startTime > this->timeOut) {
					//超时，中止虚拟机运行
					if (this->state) {
						int mask = LUA_MASKCALL |
							LUA_MASKCOUNT |
							LUA_MASKLINE |
							LUA_MASKRET;
						lua_sethook(this->state, LuaGuard::timeOutBreakHook,
							mask, 1);
					}
					return;
				}
			}
		};

	private:
		lua_State* state = nullptr;
		int timeOut = 3000;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LuaGuard)
	};

	bool LabelTemp::parseLuaLabel(
		const juce::String& data, LabelTemp::LabelData& result, double x, double& tempoTemp, uint8_t& beatTemp) const
	{
		//获取lua虚拟机
		auto ptrLState = this->luaState.get();
		if (!ptrLState) {
			return false;
		}

		//清理lua虚拟机
		lua_pushnil(ptrLState);
		lua_setglobal(ptrLState, "time");
		lua_pushnil(ptrLState);
		lua_setglobal(ptrLState, "lastTempo");
		lua_pushnil(ptrLState);
		lua_setglobal(ptrLState, "lastBeat");
		lua_pushnil(ptrLState);
		lua_setglobal(ptrLState, "tempo");
		lua_pushnil(ptrLState);
		lua_setglobal(ptrLState, "beat");
		lua_pushnil(ptrLState);
		lua_setglobal(ptrLState, "auto");

		//设置状态量
		lua_pushnumber(ptrLState, x);
		lua_setglobal(ptrLState, "time");
		lua_pushnumber(ptrLState, tempoTemp);
		lua_setglobal(ptrLState, "lastTempo");
		lua_pushinteger(ptrLState, beatTemp);
		lua_setglobal(ptrLState, "lastBeat");

		//建立守护线程
		LuaGuard guard(ptrLState);
		guard.startThread();

		//带错误处理的执行
		int err = luaL_dostring(ptrLState, data.toStdString().c_str());

		//如果守护线程仍存活，则将其关闭
		//之前想要在这里根据守护线程状态判断脚本是否超时，但应直接根据luaL_dostring返回值判断
		if (guard.isThreadRunning()) {
			guard.stopThread(3000);
		}
		
		//如果执行成功
		if (err == LUA_OK) {
			//读取tempo
			lua_getglobal(ptrLState, "tempo");
			if (lua_isnumber(ptrLState, -1)) {
				tempoTemp = lua_tonumber(ptrLState, -1);
			}
			result.tempo = tempoTemp;

			//读取beat
			lua_getglobal(ptrLState, "beat");
			if (lua_isinteger(ptrLState, -1)) {
				beatTemp = lua_tointeger(ptrLState, -1);
			}
			result.beat = beatTemp;

			//读取autoTempo
			lua_getglobal(ptrLState, "auto");
			if (lua_isboolean(ptrLState, -1)) {
				result.autoTempo = lua_toboolean(ptrLState, -1);
			}

			return true;
		}

		return false;
	}

	bool LabelTemp::parseIniLabel(
		const juce::String& data, LabelTemp::LabelData& result, double x, double& tempoTemp, uint8_t& beatTemp) const
	{
		//解析数据
		utils::ini::IniObject object(data);

		//读取tempo
		if (object.has("Label", "tempo")) {
			tempoTemp = object.get("Label", "tempo").getDoubleValue();
		}
		result.tempo = tempoTemp;

		//读取beat
		if (object.has("Label", "beat")) {
			beatTemp = object.get("Label", "beat").getIntValue();
		}
		result.beat = beatTemp;

		//读取autoTempo
		if (object.has("Label", "auto")) {
			auto sRes = object.get("Label", "auto");
			result.autoTempo =
				(sRes.isNotEmpty()) &&
				(sRes.toLowerCase() != "false") &&
				(sRes.getIntValue() != 0);
		}
		return true;
	}

	bool LabelTemp::parseXmlLabel(
		const juce::String& data, LabelTemp::LabelData& result, double x, double& tempoTemp, uint8_t& beatTemp) const
	{
		//解析数据
		auto ptrElement = juce::XmlDocument::parse(data);
		if ((!ptrElement)) {
			return false;
		}

		//查找label标签
		auto elementLabel =
			(ptrElement->getTagName() == "label") ? ptrElement.get() : ptrElement->getNextElementWithTagName("label");
		if (!elementLabel) {
			return false;
		}

		//读取tempo
		result.tempo = tempoTemp = ptrElement->getDoubleAttribute("tempo", tempoTemp);

		//读取beat
		result.beat = beatTemp = ptrElement->getIntAttribute("beat", beatTemp);

		//读取autoTempo
		{
			auto& sRes = ptrElement->getStringAttribute("auto");
			result.autoTempo =
				(sRes.isNotEmpty()) &&
				(sRes.toLowerCase() != "false") &&
				(sRes.getIntValue() != 0);
		}

		return true;
	}

	bool LabelTemp::parseJsonLabel(
		const juce::String& data, LabelTemp::LabelData& result, double x, double& tempoTemp, uint8_t& beatTemp) const
	{
		//解析数据
		auto object = juce::JSON::parse(data);
		if (!object.isObject()) {
			return false;
		}

		//读取tempo
		result.tempo = tempoTemp = object.getProperty("tempo", tempoTemp);

		//读取beat
		result.beat = beatTemp = (int)(object.getProperty("beat", (int)beatTemp));

		//读取autoTempo
		result.autoTempo = object.getProperty("auto", false);

		return true;
	}
}