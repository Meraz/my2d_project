#include <TestGame/Include/Scene/GameScene.h>

// Definition of forward declaration
#include <TestGame/Include/Entity/RenderEntity.h>
#include <TestGame/Include/Entity/PlayerEntity.h>
#include <TestGame/Include/Entity/EnemyEntity.h>
#include <TestGame/Include/Entity/ProjectileEntity.h>
#include <TestGame/Include/Entity/AnimationEntity.h>

// c++ includes
#include <fstream>

GameScene::GameScene()
{ 
	m_renderEntities		= std::vector<RenderEntity*>();
	m_enemyEntities			= std::vector<EnemyEntity*>();
	m_projectileEntities	= std::vector<ProjectileEntity*>();
	m_animationEntities		= std::vector<AnimationEntity*>();
	m_collisionEntities		= std::vector<CollisionEntity*>();
}

GameScene::~GameScene()
{
}

void GameScene::Initialize(SceneManagerInterface* p_sceneManagerInterface, Jamgine::JamgineEngine* p_engine)
{
	BaseScene::Initialize(p_sceneManagerInterface, p_engine);

	m_camera = Jamgine::Camera(0,0);
	player = new PlayerEntity();
	LoadCurrentSetup("Level.lvl");
	//player->Initialize(Jamgine::Position(200,200),Jamgine::Position(0,0),Jamgine::Position(0,0),"VAL_ANIMATION.dds",Jamgine::SpriteEffect::FLIP_NONE,250,300,0.1,0,true,Jamgine::Position(5,5)); //funkar med valtexture
	//player->AddAnimationTexture(50,50,"Anim2.dds", Jamgine::Position(3,3)); //test for multiple animations
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
	//player->Update(p_deltaTime);
}

void GameScene::CheckCollision()
{
	int projCount = m_projectileEntities.size();
	for (int i = 0; i < projCount; i++)
	{
		if (InScreen(m_projectileEntities[i]))
		{

		}
	}

	int enemyCount = m_enemyEntities.size();
	for (int i = 0; i < enemyCount; i++)
	{
		if (InScreen(m_enemyEntities[i]))
		{

		}
	}

	int collCount = m_collisionEntities.size();
	for (int i = 0; i < collCount; i++)
	{
		if (InScreen(m_collisionEntities[i]))
		{

		}
	}


	/*for (int i = 0; i < length; i++)
	{
		for (int i = 0; i < length; i++)
		{

		}
	}*/
}

bool GameScene::InScreen(CollisionEntity* entity)
{
	Position p = entity->GetPosition();
	if (m_camera.position.x - p.x > 0)
	{
		/*float width;
		if (p.x + )
		{

		}*/
	}
	return true;
}



void GameScene::Render()
{
	int max = m_renderEntities.size();
	for (unsigned int i = 0; i < max; i++)
	{
		m_renderEntities[i]->Render(m_engine);
	}
	m_engine->PostRender(&m_camera);
}


void GameScene::SaveCurrentSetup(char* p_fileName)
{
	using namespace std;

	ofstream l_file;
	l_file.open(p_fileName);

	unsigned int l_totalObjects = m_renderEntities.size();
	for (unsigned int i = 0; i < l_totalObjects; i++)
	{
		l_file << m_renderEntities[i]->ToFile().str();
		l_file << "\n";
	}
	l_file.close();
}

void GameScene::LoadCurrentSetup(char* p_fileName)
{
	using namespace std;

	ifstream l_stream;
	l_stream.open(p_fileName);

	unsigned int l_totalObjects = m_renderEntities.size();

	char l_buffer[1024];

	while (l_stream.getline(l_buffer, 1024))
	{
		char lKey[8];

		// Texture
		RenderEntity* l_renderEntity;
		sscanf_s(l_buffer, "%i ", lKey, sizeof(lKey));
		CreateObject(lKey[0], l_buffer);
	}

	l_stream.close();
}

void GameScene::CreateObject(int l_entityType, char* l_data)
{
	RenderEntity* l_entity;

	if (l_entityType == (int)ENTITY::RENDER)
	{
		l_entity = new RenderEntity();
	}
	else if (l_entityType == (int)ENTITY::COLLISION)
	{
		l_entity = new CollisionEntity();
		m_collisionEntities.push_back(static_cast<CollisionEntity*>(l_entity));
	}
	else if (l_entityType == (int)ENTITY::ANIMATION)
	{
		l_entity = new AnimationEntity();
		m_animationEntities.push_back(static_cast<AnimationEntity*>(l_entity));
	}
	else if (l_entityType == (int)ENTITY::ENENMY)
	{
		l_entity = new EnemyEntity();
		m_enemyEntities.push_back(static_cast<EnemyEntity*>(l_entity));
	}
	else if (l_entityType == (int)ENTITY::PLAYER)
	{
		ExitProcess(0);//	return; // l_entity = new RenderEntity(); // This should not happen
	}
	else if (l_entityType == (int)ENTITY::PROJECTILE)
	{
		l_entity = new ProjectileEntity();
		m_projectileEntities.push_back(static_cast<ProjectileEntity*>(l_entity));
	}
	
	l_entity->LoadClassFromData(l_data);
		
	m_renderEntities.push_back(l_entity);
}
