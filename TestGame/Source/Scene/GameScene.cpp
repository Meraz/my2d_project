#include <TestGame/Include/Scene/GameScene.h>

GameScene::GameScene()
{
	i = 0;
}

GameScene::~GameScene()
{
}

void GameScene::Initialize(SceneManagerInterface* p_sceneManagerInterface, Jamgine::JamgineEngine* p_engine)
{
	BaseScene::Initialize(p_sceneManagerInterface, p_engine);


	m_camera.position = Jamgine::Position(0,0);
}

void GameScene::Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked)
{
//		m_sceneManagerInterface->SwapSceneState(SceneState::MAIN_MENU);
	

	m_engine->PostRender(&m_camera);
}

void GameScene::Render()
{
	// Get engine pointer and call postrender, also everything else
}
