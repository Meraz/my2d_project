#pragma once

#include <Jamgine/Include/Jamgine.h>
#include <TestGame/Include/GameTimer.h>
#include <TestGame/Include/Scene/SceneManager.h>
#include <Windows.h>

class Jamgame
{

public:
	Jamgame();
	virtual ~Jamgame();
	void Initialize(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow);
	int Run();
	LRESULT CALLBACK MsgProc(HWND p_hwnd, UINT p_msg, WPARAM p_wParam, LPARAM p_lParam);


private: // Functions
	void Update();
	void Render();
	//ErrorMessage RegisterWindow();
	

private: // Variable
	// Window variables
	HINSTANCE	m_hInstance;
	HWND		m_handle;
	int			m_clientWidth;
	int			m_clientHeight;

	// Engine
	Jamgine::JamgineEngine*	m_jamgine;

	// Other
	GameTimer*	m_gameTimer;
	bool		m_gamePaused;
	float		m_mousePositionX;
	float		m_mousePositionY;
	bool		m_mouseClicked;

	// Game
	SceneManager* m_sceneManager;
};

