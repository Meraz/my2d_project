#pragma once

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