#pragma once

#include <Lua/lua.hpp>

#include <string>

class LuaManager
{
public:
	LuaManager();
	~LuaManager();
	void RegisterFunction(std::string p_functionName, int (*p_function)(lua_State* p_state));
	void RunEntireScript(char* p_path);
	void RunSpecificFuntionInScript(char* p_file, char* p_functionName);

private:
	lua_State* m_luaState;

};