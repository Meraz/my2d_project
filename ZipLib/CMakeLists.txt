# CMake settings
cmake_minimum_required(VERSION 2.8)

# Root project settings
set(ENGINE_NAME ZipLib)
project(${ENGINE_NAME})

# Set the files used in the target
file(GLOB_RECURSE HEADERS *.h)
file(GLOB_RECURSE SOURCES *.cpp)

# Add the target
add_library(${ENGINE_NAME} STATIC ${HEADERS} ${SOURCES})