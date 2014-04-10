#include <TestGame/Include/Scene/SceneManager.h>


SceneManager::SceneManager()
	: m_currentSceneState(SceneState::MAIN_MENU), m_currentScene(nullptr), m_exit(false)
{

}


void SceneManager::Initialize()
{

}

void SceneManager::Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_mouseClicked)
{
	
}

void SceneManager::Render()
{

}

void SceneManager::NotifyExit()
{

}

void SceneManager::SwapSceneState(SceneState p_sceneState)
{
	if(p_sceneState == m_currentSceneState) // Already here
		return;
	if(p_sceneState == SceneState::MAIN_MENU)
		return;
}
