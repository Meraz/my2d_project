#include <TestGame/Include/Jamgame.h>

#include <Windowsx.h>
#include <Jamgine/Include/DirectX/DirectXShared.h>

#define CLIENT_WIDTH 800
#define CLIENT_HEIGHT 800

namespace
{
	Jamgame* g_jamgame = nullptr;
}


LRESULT CALLBACK MainWndProc(HWND p_hwnd, UINT p_msg, WPARAM p_wParam, LPARAM p_lParam)
{
	// Forward hwnd on because we can get messages (e.g., WM_CREATE)
	// before CreateWindow returns, and thus before m_hMainWnd is valid.
	return g_jamgame->MsgProc(p_hwnd, p_msg, p_wParam, p_lParam);
}


Jamgame::Jamgame()
:	m_gameTimer(nullptr), m_gamePaused(false), m_mousePositionX(0), m_mousePositionY(0), m_mouseClicked(false),
	m_jamgine(nullptr), m_sceneManager(nullptr)
{
	g_jamgame = this;
	m_gameTimer = new GameTimer();
	m_sceneManager = new SceneManager();
}

Jamgame::~Jamgame()
{
	// Free everything here
}

void Jamgame::Initialize(HINSTANCE p_hInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	m_hInstance = p_hInstance;
	
	ErrorMessage hr;	
	// Jamengine
	hr = Jamgine::JamgineEngine::CreateEngine(&m_jamgine, Jamgine::GraphicalSystem::DIRECTX);
	if (hr == J_FAIL)
		return;

	Jamgine::Data_Send l_data;
	l_data.hInstance	= p_hInstance;
	l_data.messageProc	= &MainWndProc;
	l_data.clientWidth	= CLIENT_WIDTH;
	l_data.clientHeight = CLIENT_HEIGHT;

	// Init engine
	hr = m_jamgine->Initialize(l_data);

	// Gametimer
	m_gameTimer->Reset();	

	// Scenemanager
	m_sceneManager->Initialize(m_jamgine,CLIENT_WIDTH,CLIENT_HEIGHT);
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
													// Convert from top left to topright origo
	m_sceneManager->Update(m_gameTimer->DeltaTime(), m_mousePositionX, (CLIENT_HEIGHT)-40 - m_mousePositionY, m_mouseClicked);
	m_mouseClicked = false;
}

void Jamgame::Render()
{
	m_sceneManager->Render();
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
		m_mouseClicked = true;
		return 0;
	case WM_LBUTTONUP:
		m_mouseClicked = false;
		return 0;

	case WM_MOUSEMOVE:
		m_mousePositionX = GET_X_LPARAM(p_lParam);
		m_mousePositionY = GET_Y_LPARAM(p_lParam);
		return 0;
	}
	return DefWindowProc(p_hwnd, p_msg, p_wParam, p_lParam);
}