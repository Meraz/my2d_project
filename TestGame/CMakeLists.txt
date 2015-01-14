# CMake settings
cmake_minimum_required(VERSION 2.8)

# Root project settings
set(PROJECT_NAME Test_game)
project(${PROJECT_NAME})

# Set the files used in the target
file(GLOB_RECURSE HEADERS Include/*.h)
file(GLOB_RECURSE SOURCES Source/*.cpp)
set(LIBRARIES ${EXTERNAL_LIBRARIES} Jamgine SubsystemTest)

# Add the target
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

# Set SUBSYSTEM:WINDOWS
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")

# Set library search path for custom built libraries
if (NOT COMPILE_RELEASE_BUILD)
	link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Debug)
else()
	link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Release)
endif()


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
