#include <LuaModule/Include/LuaManager.h>

#include <iostream>
#include <functional>

LuaManager::LuaManager()
{
	m_luaState = luaL_newstate();

	static const luaL_Reg loadedlibs[] = {
		{ "_G", luaopen_base },
		{ LUA_LOADLIBNAME, luaopen_package },
		{ LUA_COLIBNAME, luaopen_coroutine },
		{ LUA_TABLIBNAME, luaopen_table },
		{ LUA_IOLIBNAME, luaopen_io },
		{ LUA_OSLIBNAME, luaopen_os },
		{ LUA_STRLIBNAME, luaopen_string },
		{ LUA_BITLIBNAME, luaopen_bit32 },
		{ LUA_MATHLIBNAME, luaopen_math },
		{ LUA_DBLIBNAME, luaopen_debug },
		{ NULL, NULL }
	};

	const luaL_Reg *lib = loadedlibs;
	for (; lib->func != NULL; lib++)
	{
		std::cout << " loading '" << lib->name << "'" << std::endl;
		luaL_requiref(m_luaState, lib->name, lib->func, 1);
		lua_pop(m_luaState, 1);
	}
}

LuaManager::~LuaManager()
{
	lua_close(m_luaState);
}


void LuaManager::RegisterFunction(std::string p_functionName, int (*p_function)(lua_State* p_state))
{
	lua_register(m_luaState, p_functionName.c_str(), p_function);
}

void LuaManager::RunEntireScript(char* p_path)
{
	luaL_dofile(m_luaState, p_path);
}

void LuaManager::RunSpecificFuntionInScript(char* p_path, char* p_functionName)
{
	luaL_dofile(m_luaState, p_path);
	lua_getglobal(m_luaState, p_functionName);

	lua_pcall(m_luaState, 0, LUA_MULTRET, 0);

	int argc = lua_gettop(m_luaState);
	lua_pop(m_luaState, argc);
}
