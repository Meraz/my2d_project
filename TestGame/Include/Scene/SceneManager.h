#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <TestGame\Include\Scene\BaseScene.h>
#include <TestGame\Include\Scene\SceneState.h>

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Initialize();
	void Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_mouseClicked);
	void Render();
	void NotifyExit();

private:
	void SwapSceneState(SceneState::State p_sceneState);

private:
	SceneState::State m_currentSceneState;
	BaseScene* m_currentScene;
	bool m_Exit;

};
#endif