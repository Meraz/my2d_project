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

	m_engine->LoadTexture(&a,"Alpha.dds");
	m_engine->LoadTexture(&b,"Circle.dds");
	m_engine->LoadTexture(&c,"Box1.dds");
	m_engine->LoadTexture(&d,"Anim1.dds");
	m_engine->LoadTexture(&e,"Anim2.dds");
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
