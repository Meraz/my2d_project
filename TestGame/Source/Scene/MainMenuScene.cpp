#include <TestGame/Include/Scene/MainMenuScene.h>

MainMenuScene::MainMenuScene()
{
	i = 0;
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::Initialize(SceneManagerInterface* p_sceneManagerInterface, Jamgine::JamgineEngine* p_engine)
{
	BaseScene::Initialize(p_sceneManagerInterface,p_engine);
}

void MainMenuScene::Update(double p_deltaTime, float p_mousePositionX, float p_mousePositionY, bool p_lMouseClicked)
{
//	if (++i > 500)
	m_sceneManagerInterface->SwapSceneState(SceneState::GAME);

}

void MainMenuScene::Render()
{
}
