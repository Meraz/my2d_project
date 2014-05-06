find_path(LUA_INCLUDE_DIRS
    Lua/lua.hpp
    HINTS "${CMAKE_SOURCE_DIR}/External/Include")

find_path(LUA_LIBRARY_PATH
    NAMES lua_lib.lib
    HINTS "${CMAKE_SOURCE_DIR}/External/Lib/x86")