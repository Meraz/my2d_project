#pragma once

//#include <TestGame/Include/Scene/SceneManagerInterface.h>
#include <TestGame/Include/Scene/BaseScene.h>
#include <Windows.h>

class SceneManager : public SceneManagerInterface
{
public:
	SceneManager();
	~SceneManager();

	void Initialize(Jamgine::JamgineEngine* p_engine, HWND p_handle);
	void Update(double p_deltaTime, float p_mousePositionX, float p_mousePositionY, bool p_mouseClicked);
	void Render();

	// Inherited functions
	void NotifyExit();
	void SwapSceneState(SceneState p_sceneState);

private:
	SceneState m_currentSceneState;
	BaseScene* m_currentScene;
	bool m_exit;
	Jamgine::JamgineEngine* m_engine;
	HWND m_handle = nullptr;

};