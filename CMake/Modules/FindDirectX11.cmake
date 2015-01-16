find_path(DIRECTX11_INCLUDE_DIRS
    DirectX/D3D11.h
    HINTS "${CMAKE_SOURCE_DIR}/External/Include")

find_library(DIRECTX11_LIBRARY
    NAMES d3d11.lib
    HINTS "${CMAKE_SOURCE_DIR}/External/Lib/x86")
	
find_library(DIRECTX11_COMPILER_LIBRARY
    NAMES d3dcompiler.lib
    HINTS "${CMAKE_SOURCE_DIR}/External/Lib/x86")
	
find_library(DIRECTX11_DXGUID_LIBRARY
    NAMES dxguid.lib
    HINTS "${CMAKE_SOURCE_DIR}/External/Lib/x86")
	
find_library(DIRECTX11_LIBRARY_64
	NAMES d3d11.lib
	HINTS "${CMAKE_SOURCE_DIR}/External/Lib/x64") 