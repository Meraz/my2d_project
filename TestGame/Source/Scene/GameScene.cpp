#include <TestGame/Include/Scene/GameScene.h>

// Definition of forward declaration
#include <TestGame/Include/Entity/GameEntity.h>
#include <TestGame/Include/Entity/RenderEntity.h>

GameScene::GameScene()
{ 
	m_gameEntity	= std::vector<GameEntity*>();
	m_renderEntity	= std::vector<RenderEntity*>();
}

GameScene::~GameScene()
{
}

void GameScene::Initialize(SceneManagerInterface* p_sceneManagerInterface, Jamgine::JamgineEngine* p_engine)
{
	for (unsigned int y = 0; y < 100; y++)
	{
		for (unsigned int x = 0; x < 100; x++)
		{
			m_renderEntity.push_back(new RenderEntity());
//			m_renderEntity[y+x]->Initialize(Position(), p_texture, float p_width, float p_height);
		}
	}
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
	

}

void GameScene::Render()
{
	// Get engine pointer and call postrender, also everything else
}
