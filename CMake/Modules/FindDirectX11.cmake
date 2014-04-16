find_path(DIRECTX11_INCLUDE_DIRS
    DirectX/D3D11.h
    HINTS "${CMAKE_SOURCE_DIR}/External/Include")

find_path(DIRECTX11_LIBRARY
    NAMES d3d11.lib
    HINTS "${CMAKE_SOURCE_DIR}/External/Lib/x86")
	
find_path(DIRECTX11_LIBRARY_64
	NAMES d3d11.lib
	HINTS "${CMAKE_SOURCE_DIR}/External/Lib/x64") 