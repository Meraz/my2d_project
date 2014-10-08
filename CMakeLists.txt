# CMake settings
cmake_minimum_required(VERSION 2.8)

# Root project settings
set(SOLUTION_NAME Jamgine)
project(${SOLUTION_NAME})

# SET OUTPUTFOLDER FOR ALL SUBPROJECTS
set(OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${OUTPUT_DIRECTORY} CACHE PATH "Build directory" FORCE)
set(LIBRARY_OUTPUT_PATH ${OUTPUT_DIRECTORY} CACHE PATH "Build directory" FORCE)

# Find external libraries
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/Modules/")

find_package(DIRECTX11 REQUIRED)
find_package(FMOD REQUIRED)
find_package(ZLIB REQUIRED)

set(EXTERNAL_INCLUDE_DIRS 
	${DIRECTX11_INCLUDE_DIRS}
	${FMOD_INCLUDE_DIRS}
	${ZLIB_INCLUDE_DIRS}
		
)
	
set(EXTERNAL_LIBRARIES
	${DIRECTX11_LIBRARY}
	${FMOD_LIBRARY_PATH}
	${ZLIB_LIBRARY}
)

# Set global compiler options
add_definitions(-DUNICODE -D_UNICODE)

include_directories(${EXTERNAL_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR})

# Add subdirectories
add_subdirectory(Jamgine)
add_subdirectory(TestGame)
