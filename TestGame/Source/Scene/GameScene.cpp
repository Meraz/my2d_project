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
	BaseScene::Initialize(p_sceneManagerInterface, p_engine);

	m_camera = Jamgine::Camera(0,0);

	m_engine->LoadTexture(&a, "Box1.dds");
	m_engine->LoadTexture(&b, "Circle.dds");


	int i = 0;
	for (unsigned int y = 0; y < 10; y++)
	{
		for (unsigned int x = 0; x < 10; x++)
		{
			m_renderEntity.push_back(new RenderEntity());
			m_renderEntity[10*y+x]->Initialize(Position(x*50,y*50), a, 50, 50);
		}
	}
	
}

void GameScene::Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked)
{

}

void GameScene::Render()
{
	for (int i = 0; i < 10 * 10; i++)
	{
		m_renderEntity[i]->Render(m_engine);
	}
	m_engine->PostRender(&m_camera);
}
