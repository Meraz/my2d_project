# CMake settings
cmake_minimum_required(VERSION 2.8)

# Root project settings
set(PROJECT_NAME_TESTGAME Test_game)
project(${PROJECT_NAME_TESTGAME})

# Set the files used in the target
file(GLOB_RECURSE SOURCES Source/*.cpp)
file(GLOB_RECURSE HEADERS Include/*.h)

set(LIBRARIES ${EXTERNAL_LIBRARIES}) # No idea what this is

# Set search paths
include_directories(Include)		 # No idea what this is

# Set library search path
link_directories(${CMAKE_BINARY_DIR}/Jamgine/Debug)

# Add the target
add_executable(${PROJECT_NAME_TESTGAME} ${HEADERS} ${SOURCES})

# Additional lib
target_link_libraries(${PROJECT_NAME_TESTGAME} Jamgine.lib)
target_link_libraries(${PROJECT_NAME_TESTGAME} d3d11.lib)
target_link_libraries(${PROJECT_NAME_TESTGAME} d3dcompiler.lib)
target_link_libraries(${PROJECT_NAME_TESTGAME} dxguid.lib)
target_link_libraries(${PROJECT_NAME_TESTGAME} Xinput9_1_0.lib)


# Set SUBSYSTEM:WINDOWS
set_target_properties(${PROJECT_NAME_TESTGAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin})
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release})

# Copy game resources
add_custom_target(_resourceCopy ALL 
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Resources ${CMAKE_BINARY_DIR}/bin/Resources
)

# Copy dependencies
add_custom_target(_dependencies ALL 
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/External/Lib ${CMAKE_BINARY_DIR}/bin/External
)
