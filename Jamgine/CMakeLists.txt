# CMake settings
cmake_minimum_required(VERSION 2.8)

# Root project settings
set(PROJECT_NAME Jamgine)
project(${PROJECT_NAME})

# Set the files used in the target
file(GLOB_RECURSE HEADERS Include/*.h)
file(GLOB_RECURSE SOURCES Source/*.cpp)

# Set search paths
include_directories(Include)

# Add subdirectories
add_subdirectory(DirectX11)
add_subdirectory(OpenGL)
	
# Add the target
add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${LIBRARIES})


