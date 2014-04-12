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
}

void GameScene::Update(double p_deltaTime, float p_mousePositionX, float p_mousePositionY, bool p_lMouseClicked)
{
	
	/* iterate collision objects
	for(int i = 0; i < m_collisionEntity.size(); i++)
	{
		for(int j = 0; j < m_collisionEntity.size(); j++)
		{
			if(m_collisionEntity.at(j) == m_collisionEntity.at(i)){}
			else
			{
				if(collisionCheck(m_collisionEntity.at(i), m_collisionEntity.at(j)))
				{
					if(m_collisionEntity.at(i)->getType() == m_collisionEntity.at(j)->getType())
					{
						won't work, figure shiet aut
					}
				}
			}
		}
	}
	*/
}

void GameScene::Render()
{
	m_engine->PostRender(&m_camera);
}


void GameScene::SaveCurrentSetup(char* p_fileName)
{

}

void GameScene::LoadCurrentSetup(char* p_fileName)
{

}
