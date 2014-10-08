find_path(ZLIB_INCLUDE_DIRS
    Zlib/zconf.h
    HINTS "${CMAKE_SOURCE_DIR}/External/Include")

find_path(ZLIB_LIBRARY_PATH
    NAMES zdll.lib
    HINTS "${CMAKE_SOURCE_DIR}/External/Lib/x86")

