# CMake settings
cmake_minimum_required(VERSION 2.8)

# Root project settings
set(PROJECT_NAME TestGame)
project(${PROJECT_NAME})

# Set the files used in the target
file(GLOB_RECURSE SOURCES Source/*.cpp)
file(GLOB_RECURSE HEADERS Include/*.h)

set(LIBRARIES ${EXTERNAL_LIBRARIES})

# Set search paths
include_directories(Include)

# Add the target
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} C:/Users/Bulten/ssp/Build/Jamgine/Debug/Jamgine.lib)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} C:/Users/Bulten/ssp/Build/Jamgine/DirectX11/Debug/DirectX11.lib)