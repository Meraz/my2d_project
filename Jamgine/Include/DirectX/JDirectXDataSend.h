#pragma once

#include <Jamgine/Include/DirectX/JDirectXShared.h>

#include <DirectX/d3d11_1.h>

namespace Jamgine
{
	struct Data_Send
	{
		HINSTANCE hInstance;
		LRESULT (CALLBACK *messageProc)(HWND, UINT, WPARAM, LPARAM); 
		int clientWidth;
		int clientHeight;
	};
};