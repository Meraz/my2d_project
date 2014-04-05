#pragma once

namespace Jamgine
{
	struct Data_Send
	{
		HWND l_handle;
		HINSTANCE l_hInstance;
		LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
		int p_clientWidth;
		int p_clientHeight;
	};
};