#include <TestGame/Include/Scene/SceneManager.h>
#include <TestGame/Include/Scene/GameScene.h>
#include <TestGame/Include/Scene/MainMenuScene.h>
#include <TestGame/Include/Scene/EditScene.h>


SceneManager::SceneManager()
	: m_currentSceneState(SceneState::NONE), m_currentScene(nullptr), m_exit(false)
{

}


void SceneManager::Initialize(Jamgine::JamgineEngine* p_engine, float width, float height)
{
	m_width = width;
	m_height = height;
	m_engine = p_engine;

	SwapSceneState(SceneState::GAME);
}

void SceneManager::Update(double p_deltaTime, float p_mousePositionX, float p_mousePositionY, bool p_mouseClicked)
{
	m_currentScene->Update(p_deltaTime, p_mousePositionX, p_mousePositionY, p_mouseClicked);
}

void SceneManager::Render()
{
	m_currentScene->Render();
}

void SceneManager::NotifyExit()
{
	// Do something here
	exit(0);
}

void SceneManager::SwapSceneState(SceneState p_sceneState)
{
	if (p_sceneState == m_currentSceneState) // Already here, nothing to do, return.
	{
		return;
	}
	
	// Delete old scene
	if (m_currentScene != nullptr)
	{
		delete m_currentScene;
		m_currentScene = nullptr; // Set it to nullptr
	}

	// Check for new screen
	if (p_sceneState == SceneState::MAIN_MENU)
	{
		m_currentScene = new MainMenuScene();
	}
	else if (p_sceneState == SceneState::GAME)
	{
		m_currentScene = new GameScene(m_width,m_height);
	}
	else if (p_sceneState == SceneState::EDIT)
	{
		m_currentScene = new EditScene();
	}
	else // Nothing to do, return
	{
		return; 
	}

	// Initialize new screen, if it's not a nullptr
	if (m_currentScene != nullptr)
	{
		m_currentScene->Initialize((SceneManagerInterface*)this,m_engine);
		m_currentSceneState = p_sceneState; // Save knowledge for new state
	}
}
