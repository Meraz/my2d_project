#pragma once

//#include <TestGame/Include/Scene/SceneManagerInterface.h>
#include <TestGame/Include/Scene/BaseScene.h>

class SceneManager : public SceneManagerInterface
{
public:
	SceneManager();
	~SceneManager();

	void Initialize();
	void Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_mouseClicked);
	void Render();

	// Inherited functions
	void NotifyExit();
	void SwapSceneState(SceneState p_sceneState);

private:
	SceneState m_currentSceneState;
	BaseScene* m_currentScene;
	bool m_exit;

};