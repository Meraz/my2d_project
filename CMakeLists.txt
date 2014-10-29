# CMake settings
cmake_minimum_required(VERSION 2.8)

# Root project settings
set(SOLUTION_NAME Jamgine)
project(${SOLUTION_NAME})

option(COMPILE_RELEASE_BUILD "Release build (Unchecked is debug)" OFF)
option(COMPILE_64_BIT_BUILD "64 bit build (Unchecked is 64bit)" OFF)

if(NOT COMPILE_64_BIT_BUILD)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/32)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/32)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/32)
	else()	
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/64)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/64)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/64)
endif()

#set(LIBRARY_OUTPUT_PATH ${OUTPUT_DIRECTORY} CACHE PATH "Build directory" FORCE) # This should now be needed, however, I do not dare to remove it just yet.

# Find external libraries
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/Modules/")

find_package(DIRECTX11 REQUIRED)

set(EXTERNAL_INCLUDE_DIRS 
	${DIRECTX11_INCLUDE_DIRS}
)
	
set(EXTERNAL_LIBRARIES
	${DIRECTX11_LIBRARY}
)

# Set global compiler options
add_definitions(-DUNICODE -D_UNICODE)

include_directories(${EXTERNAL_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR})

# Add subdirectories
add_subdirectory(Jamgine)
add_subdirectory(TestGame)

# ziplib, lazy include. Could pack em in one folder etc etc
add_subdirectory(ZipLib)
add_subdirectory(bzip2)
add_subdirectory(lzma)
add_subdirectory(zlib)
