# CMake settings
cmake_minimum_required(VERSION 2.8)

# Root project settings
set(PROJECT_NAME_TESTGAME Test_game)
project(${PROJECT_NAME_TESTGAME})

# Set the files used in the target
file(GLOB_RECURSE HEADERS Include/*.h)
file(GLOB_RECURSE SOURCES Source/*.cpp)

# Set library search path for custom buildt libraries
if (NOT COMPILE_RELEASE_BUILD)
	link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Debug)
else()
	link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Release)
endif()
link_directories(${EXTERNAL_LIBRARIES})	# This does not seem to work, why?


# Move external dlls to executing folder
if(COMPILE_64_BIT_BUILD)
	add_custom_target(_dependencies ALL 
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/External/Dll/x64 ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Debug
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/External/Dll/x64 ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Release
	)
else()
	add_custom_target(_dependencies ALL 
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/External/Dll/x86 ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Debug
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/External/Dll/x86 ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Release
	)
endif()


# Add the target
add_executable(${PROJECT_NAME_TESTGAME} ${HEADERS} ${SOURCES})

# Additional lib
target_link_libraries(${PROJECT_NAME_TESTGAME} d3d11.lib)
target_link_libraries(${PROJECT_NAME_TESTGAME} d3dcompiler.lib)
target_link_libraries(${PROJECT_NAME_TESTGAME} dxguid.lib)
target_link_libraries(${PROJECT_NAME_TESTGAME} lzma.lib)
target_link_libraries(${PROJECT_NAME_TESTGAME} ZipLib.lib)
target_link_libraries(${PROJECT_NAME_TESTGAME} bzip2.lib)
target_link_libraries(${PROJECT_NAME_TESTGAME} zlib.lib)

# Graphics
target_link_libraries(${PROJECT_NAME_TESTGAME} Jamgine.lib)

# Set SUBSYSTEM:WINDOWS
set_target_properties(${PROJECT_NAME_TESTGAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")

# Copy game resources
add_custom_target(_resourceCopy ALL 
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Resources/HLSL ${CMAKE_BINARY_DIR}/TestGame
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Resources/Level ${CMAKE_BINARY_DIR}/TestGame
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Resources/Texture ${CMAKE_BINARY_DIR}/TestGame
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Resources/Archives ${CMAKE_BINARY_DIR}/TestGame
)
