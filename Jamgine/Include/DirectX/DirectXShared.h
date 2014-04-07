#pragma once

namespace Jamgine
{
	struct Data_Send
	{
//		HWND** handle;
		HINSTANCE hInstance;
		LRESULT (CALLBACK *messageProc)(HWND, UINT, WPARAM, LPARAM); 
		int clientWidth;
		int clientHeight;
	};
};