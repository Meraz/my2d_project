# CMake settings
cmake_minimum_required(VERSION 2.8)

# Root project settings
set(LIBNAME lua_lib)
project(${LIBNAME})

# Set the files used in the target
file(GLOB_RECURSE HEADERS Include/*.h)
file(GLOB_RECURSE SOURCES Source/*.cpp)


# Add the target
add_library(${LIBNAME} SHARED ${HEADERS} ${SOURCES})