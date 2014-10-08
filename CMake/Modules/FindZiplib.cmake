find_path(ZIPLIB_INCLUDE_DIRS
    ziplib/ZipFile.h
    HINTS "${CMAKE_SOURCE_DIR}/External/Include")

find_path(ZIPLIB_LIBRARY_PATH
    NAMES zdll.lib bzip2.lib lzma.lib ZipLip.lib zlib.lib
    HINTS "${CMAKE_SOURCE_DIR}/External/Lib/x86")

