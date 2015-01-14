# CMake settings
cmake_minimum_required(VERSION 2.8)

# Root project settings
set(PROJECT_NAME_TEST SubsystemTest)
project(${PROJECT_NAME_TEST})

# Set the files used in the target
file(GLOB_RECURSE HEADERS Headers/*.h)
file(GLOB_RECURSE SOURCES Source/*.cpp)
set(LIBRARIES ${EXTERNAL_LIBRARIES})

add_library(${PROJECT_NAME_TEST} SHARED ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})