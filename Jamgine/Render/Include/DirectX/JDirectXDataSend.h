#pragma once

#include <Jamgine/Render/Include/DirectX/JDirectXShared.h>

#include <DirectX/d3d11_1.h>

namespace Jamgine
{
	namespace Render {

		struct Data_Send
		{
			HINSTANCE hInstance;
			LRESULT(CALLBACK *messageProc)(HWND, UINT, WPARAM, LPARAM);
			unsigned int clientWidth;
			unsigned int clientHeight;
		};
	}
};