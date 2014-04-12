#include <TestGame/Include/Scene/GameScene.h>

GameScene::GameScene()
{
	i = 0;
}

GameScene::~GameScene()
{
}

void GameScene::Initialize(SceneManagerInterface* p_sceneManagerInterface)
{
	BaseScene::Initialize(p_sceneManagerInterface);
}

void GameScene::Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked)
{
//		m_sceneManagerInterface->SwapSceneState(SceneState::MAIN_MENU);

	for (int i = 0; i < 100; i++)
	{

	}
}

void GameScene::Render()
{
	// Get engine pointer and call postrender, also everything else
}
