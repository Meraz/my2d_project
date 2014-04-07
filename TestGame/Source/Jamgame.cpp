#include "Jamgame.h"

#include <Windowsx.h>
#include <Jamgine/Include/DirectX/DirectXShared.h>

namespace
{
	Jamgame* g_jamgame = nullptr;
}

// Forwards declarion for MsgProc
//LRESULT CALLBACK MsgProc(HWND p_hwnd, UINT p_msg, WPARAM p_wParam, LPARAM p_lParam);

LRESULT CALLBACK MainWndProc(HWND p_hwnd, UINT p_msg, WPARAM p_wParam, LPARAM p_lParam)
{
	// Forward hwnd on because we can get messages (e.g., WM_CREATE)
	// before CreateWindow returns, and thus before m_hMainWnd is valid.
	return g_jamgame->MsgProc(p_hwnd, p_msg, p_wParam, p_lParam);
}


Jamgame::Jamgame()
:	m_gameTimer(nullptr), m_gamePaused(false), m_mousePositionX(0), m_mousePositionY(0), m_lMouseClicked(false),
	m_jamgine(nullptr)
{
	g_jamgame = this;
}

Jamgame::~Jamgame()
{
	// Free everything here
}

void Jamgame::Initialize(HINSTANCE p_hInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	m_hInstance = p_hInstance;

	
	WNDCLASS l_wndClass;
	l_wndClass.style         = CS_HREDRAW | CS_VREDRAW;
	l_wndClass.lpfnWndProc   = MainWndProc; 
	l_wndClass.cbClsExtra    = 0;
	l_wndClass.cbWndExtra    = 0;
	l_wndClass.hInstance     = p_hInstance;
	l_wndClass.hIcon         = LoadIcon(0, IDI_APPLICATION);
	l_wndClass.hCursor       = LoadCursor(0, IDC_ARROW);
	l_wndClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	l_wndClass.lpszMenuName  = 0;
	l_wndClass.lpszClassName = L"D3DWndClassName";
			
	if (!RegisterClass(&l_wndClass))
		return;// J_FAIL;
	
	ErrorMessage hr;
	
	// Register window
	hr = RegisterWindow();
	if(hr == J_FAIL)
		return;

	// Jamengine
	hr = Jamgine::JamgineEngine::CreateEngine(&m_jamgine, Jamgine::GraphicalSystem::DIRECTX);
	if (hr == J_FAIL)
		return;

	// Init engine

	// Gametimer
	m_gameTimer = new GameTimer();
	m_gameTimer->Reset();




	Jamgine::Data_Send l_data;
//	l_data.handle		= 0;
	l_data.hInstance	= p_hInstance;
//	l_data.messageProc	= &MsgProc;
	l_data.clientWidth	= 800;
	l_data.clientHeight = 800;


	hr = m_jamgine->Initialize(l_data);
}

int Jamgame::Run()
{
	MSG l_msg = { 0 };
	
	while (l_msg.message != WM_QUIT)
	{
		// If there are Window messages then process them.
		if (PeekMessage(&l_msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&l_msg);
			DispatchMessage(&l_msg);
		}
		else
		{
			m_gameTimer->Tick();
			if (!m_gamePaused)
			{
				Update();
				Render();
			}
			else
			{
				Sleep(100);
			}
		}
	}
	return 1;
}

void Jamgame::Update()
{

}

void Jamgame::Render()
{

}

ErrorMessage Jamgame::RegisterWindow()
{
	ErrorMessage l_errorMessage = J_OK;

	WNDCLASSEX l_wndClass;
	l_wndClass.style         = CS_HREDRAW | CS_VREDRAW;
	l_wndClass.lpfnWndProc   = MainWndProc; 
	l_wndClass.cbClsExtra    = 0;
	l_wndClass.cbWndExtra    = 0;
	l_wndClass.hInstance     = m_hInstance;
	l_wndClass.hIcon         = LoadIcon(0, IDI_APPLICATION);
	l_wndClass.hCursor       = LoadCursor(0, IDC_ARROW);
	l_wndClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	l_wndClass.lpszMenuName  = 0;
	l_wndClass.lpszClassName = L"D3DWndClassName";
			
	if (!RegisterClassEx(&l_wndClass))
		return J_FAIL;

				
	// Create window
	RECT rc = { 0, 0, m_clientHeight, m_clientWidth};
	//AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	m_handle = CreateWindow(
		L"TestGame",
		L"Welcome to this window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		rc.right - rc.left,
		rc.bottom - rc.top,
		NULL,
		NULL, 
		m_hInstance, 
		NULL);
	if(m_handle == NULL)
		return J_FAIL;

	return l_errorMessage;
}



LRESULT CALLBACK Jamgame::MsgProc(HWND p_hwnd, UINT p_msg, WPARAM p_wParam, LPARAM p_lParam)
{
	switch (p_msg)
	{
		// WM_ACTIVATE is sent when the window is activated or deactivated.  
		// We pause the game when the window is deactivated and unpause it 
		// when it becomes active.  
	case WM_ACTIVATE:
		if (LOWORD(p_wParam) == WA_INACTIVE)
		{
			//m_appPaused = true;
			//m_gameTimer->Stop();
		}
		else
		{
			//m_appPaused = false;
			//m_gameTimer->Start();
		}
		return 0;

		// WM_DESTROY is sent when the window is being destroyed.
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

		// The WM_MENUCHAR message is sent when a menu is active and the user presses 
		// a key that does not correspond to any mnemonic or accelerator key. 
	case WM_MENUCHAR:
		// Don't beep when we alt-enter.
		return MAKELRESULT(0, MNC_CLOSE);
	case WM_LBUTTONDOWN:
//		g_jamgame->m_lMouseClicked = true;
		return 0;
	case WM_LBUTTONUP:
//		m_lMouseClicked = false;
		return 0;

	case WM_MOUSEMOVE:
//		m_mousePositionX = GET_X_LPARAM(p_lParam);
//		m_mousePositionY = GET_Y_LPARAM(p_lParam);
		return 0;
	}
	return DefWindowProc(p_hwnd, p_msg, p_wParam, p_lParam);
}