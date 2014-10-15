# CMake settings
cmake_minimum_required(VERSION 2.8)

# Root project settings
set(PROJECT_NAME_TESTGAME Test_game)
project(${PROJECT_NAME_TESTGAME})

# Set the files used in the target
file(GLOB_RECURSE SOURCES Source/*.cpp)
file(GLOB_RECURSE HEADERS Include/*.h)

# Set library search path
link_directories(${EXTERNAL_LIBRARIES})
if (NOT COMPILE_RELEASE_BUILD)
	link_directories(${OUTPUT_DIRECTORY}/Debug)
else()
	link_directories(${OUTPUT_DIRECTORY}/Release)
endif()


# Add the target
add_executable(${PROJECT_NAME_TESTGAME} ${HEADERS} ${SOURCES})

# Additional lib
target_link_libraries(${PROJECT_NAME_TESTGAME} d3d11.lib)
target_link_libraries(${PROJECT_NAME_TESTGAME} d3dcompiler.lib)
target_link_libraries(${PROJECT_NAME_TESTGAME} dxguid.lib)
target_link_libraries(${PROJECT_NAME_TESTGAME} Xinput9_1_0.lib)
target_link_libraries(${PROJECT_NAME_TESTGAME} fmod_vc.lib)
target_link_libraries(${PROJECT_NAME_TESTGAME} lzma.lib)
target_link_libraries(${PROJECT_NAME_TESTGAME} ZipLib.lib)
target_link_libraries(${PROJECT_NAME_TESTGAME} bzip2.lib)
target_link_libraries(${PROJECT_NAME_TESTGAME} zlib.lib)


target_link_libraries(${PROJECT_NAME_TESTGAME} Jamgine.lib)

# Set SUBSYSTEM:WINDOWS
set_target_properties(${PROJECT_NAME_TESTGAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")

# Copy game resources
add_custom_target(_resourceCopy ALL 
#	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Resources ${CMAKE_BINARY_DIR}/build/Resources
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Resources/HLSL ${CMAKE_BINARY_DIR}/TestGame
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Resources/Level ${CMAKE_BINARY_DIR}/TestGame
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Resources/Texture ${CMAKE_BINARY_DIR}/TestGame
)

add_custom_target(_dependencies ALL 
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/External/Dll ${OUTPUT_DIRECTORY}/Debug
)