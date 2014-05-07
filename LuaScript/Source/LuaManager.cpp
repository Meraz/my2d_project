#include <LuaScript/Include/LuaManager.h>

#include <iostream>


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

}