# CMake settings
cmake_minimum_required(VERSION 2.8)

# Root project settings
set(PROJECT_NAME Memory)
project(${PROJECT_NAME})

# Set the files used in the target
file(GLOB_RECURSE HEADERS Include/*.h)
file(GLOB_RECURSE SOURCES Source/*.cpp)

# Add the target
add_library(${PROJECT_NAME} SHARED ${HEADERS} ${SOURCES})