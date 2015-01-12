# CMake settings
cmake_minimum_required(VERSION 2.8)

# Root project settings
set(PROJECT_NAME_TEST SubsystemTest)
project(${PROJECT_NAME_TEST})

# Set the files used in the target
file(GLOB_RECURSE HEADERS Include/*.h)
file(GLOB_RECURSE HEADERS Include/*.hpp)
file(GLOB_RECURSE SOURCES Source/*.cpp)

add_library(${PROJECT_NAME_TEST} SHARED ${HEADERS} ${SOURCES})