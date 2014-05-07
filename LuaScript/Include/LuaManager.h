#pragma once

#include <Lua/lua.hpp>

class LuaManager
{
public:
	LuaManager();
	~LuaManager();
	void RegisterFunction();
	void RunScript(char* p_path);

private:
	lua_State* m_luaState;

};