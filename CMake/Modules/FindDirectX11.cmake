# Find the OpenGL Extension Wrangler library

find_path(DIRECTX11_INCLUDE_DIRS
    DirectX/D3D11.h
    HINTS "${CMAKE_SOURCE_DIR}/External/Include")

find_library(DIRECTX11_LIBRARY
    NAMES d3d11
    HINTS "${CMAKE_SOURCE_DIR}/External/Lib/x86")
	
find_library(DIRECTX11_LIBRARY_64
	NAMES d3d11
	HINTS "${CMAKE_SOURCE_DIR}/External/Lib/x64") 