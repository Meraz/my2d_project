# CMake settings
cmake_minimum_required(VERSION 2.8)

# Root project settings
set(PROJECT_NAME TestGame)
project(${PROJECT_NAME})

# Set the files used in the target
file(GLOB_RECURSE SOURCES Source/*.cpp)
file(GLOB_RECURSE HEADERS Include/*.h)

set(LIBRARIES ${EXTERNAL_LIBRARIES}) # No idea what this is

# Set search paths
include_directories(Include)		 # No idea what this is

# Set library search path
link_directories(${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Jamgine/Debug)

# Add the target
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# Additional lib
target_link_libraries(${PROJECT_NAME} Jamgine.lib)

# Set SUBSYSTEM:WINDOWS
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")