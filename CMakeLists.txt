# CMake settings
cmake_minimum_required(VERSION 2.8)

# Root project settings
set(SOLUTION_NAME Jamgine)
project(${SOLUTION_NAME})

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

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
#add_definitions(-DWIN32_LEAN_AND_MEAN)
#add_definitions(-D_SCL_SECURE_NO_WARNINGS)
# add_definitions(/wd4005)    # Disable macro redefinition warning

include_directories(${EXTERNAL_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR})

# Add subdirectories
add_subdirectory(Jamgine)
add_subdirectory(TestGame)
