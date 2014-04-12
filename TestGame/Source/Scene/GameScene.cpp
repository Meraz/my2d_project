#include <TestGame/Include/Scene/GameScene.h>

// Definition of forward declaration
#include <TestGame/Include/Entity/RenderEntity.h>
#include <TestGame/Include/Entity/PlayerEntity.h>

GameScene::GameScene()
{ 
	m_renderEntity	= std::vector<RenderEntity*>();
}

GameScene::~GameScene()
{
}

void GameScene::Initialize(SceneManagerInterface* p_sceneManagerInterface, Jamgine::JamgineEngine* p_engine)
{
	BaseScene::Initialize(p_sceneManagerInterface, p_engine);

	m_camera = Jamgine::Camera(0,0);

	for (unsigned int y = 0; y < 10; y++)
	{
		for (unsigned int x = 0; x < 10; x++)
		{
			m_renderEntity.push_back(new PlayerEntity());
			m_renderEntity[10*y+x]->Initialize(Position(x*50,y*50), "Box1.dds", 50, 50);
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


void GameScene::SaveCurrentSetup(char* p_fileName)
{

}

void GameScene::LoadCurrentSetup(char* p_fileName)
{

}