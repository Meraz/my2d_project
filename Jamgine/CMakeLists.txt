# CMake settings
cmake_minimum_required(VERSION 2.8)

# Root project settings
set(ENGINE_NAME Jamgine)
project(${ENGINE_NAME})

# Set the files used in the target
file(GLOB_RECURSE HEADERS Include/*.h)
file(GLOB_RECURSE SOURCES Source/*.cpp)

# Set search paths
#include_directories(Include)

# Add the target
add_library(${ENGINE_NAME} STATIC ${HEADERS} ${SOURCES})