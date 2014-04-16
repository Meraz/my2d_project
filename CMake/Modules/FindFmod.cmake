find_path(FMOD_INCLUDE_DIRS
    Fmod/Fmod.hpp
    HINTS "${CMAKE_SOURCE_DIR}/External/Include")

find_path(FMOD_LIBRARY_PATH
    NAMES fmod_vc.lib
    HINTS "${CMAKE_SOURCE_DIR}/External/Lib/x86")