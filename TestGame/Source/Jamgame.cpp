#include "Jamgame.h"

#include <Windowsx.h>

Jamgame::Jamgame()
:	m_gameTimer(nullptr), m_clientWidth(800), m_clientHeight(800), m_gamePaused(false), m_mousePositionX(0), m_mousePositionY(0), m_lMouseClicked(false),
	m_jamgine(nullptr)
{

}

Jamgame::~Jamgame()
{
}

void Jamgame::Initialize()
{
	ErrorMessage hr;

	m_gameTimer = new GameTimer();
	m_gameTimer->Reset();


	hr = Jamgine::JamgineEngine::CreateEngine(&m_jamgine, Jamgine::GraphicalSystem::DIRECTX);
	if (hr == J_FAIL)
		return;

	hr = m_jamgine->Initialize(&m_handle, m_hInstance, );
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

LRESULT Jamgame::MsgProc(HWND p_hwnd, UINT p_msg, WPARAM p_wParam, LPARAM p_lParam)
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
		m_lMouseClicked = true;
		return 0;
	case WM_LBUTTONUP:
		m_lMouseClicked = false;
		return 0;

	case WM_MOUSEMOVE:
		m_mousePositionX = GET_X_LPARAM(p_lParam);
		m_mousePositionY = GET_Y_LPARAM(p_lParam);
		return 0;
	}
	return DefWindowProc(p_hwnd, p_msg, p_wParam, p_lParam);
}