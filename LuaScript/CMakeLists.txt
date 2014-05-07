# CMake settings
cmake_minimum_required(VERSION 2.8)

# Root project settings
set(LIBNAME Jamgine_lua)
project(${LIBNAME})

# Set the files used in the target
file(GLOB_RECURSE HEADERS Include/*.h)
file(GLOB_RECURSE SOURCES Source/*.cpp)

# Set search paths

# Add the target
add_library(${LIBNAME} STATIC ${HEADERS} ${SOURCES})