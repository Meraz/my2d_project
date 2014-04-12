#include <TestGame/Include/Scene/MainMenuScene.h>

MainMenuScene::MainMenuScene()
{
	i = 0;
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::Initialize(SceneManagerInterface* p_sceneManagerInterface)
{
	BaseScene::Initialize(p_sceneManagerInterface);
}

void MainMenuScene::Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked)
{
//	if (++i > 500)
	m_sceneManagerInterface->SwapSceneState(SceneState::GAME);

}

void MainMenuScene::Render()
{
}
