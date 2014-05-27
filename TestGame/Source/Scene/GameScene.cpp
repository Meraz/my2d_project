#include <TestGame/Include/Scene/GameScene.h>

// Definition of forward declaration
#include <TestGame/Include/Entity/RenderEntity.h>
#include <TestGame/Include/Entity/PlayerEntity.h>
#include <TestGame/Include/Entity/EnemyEntity.h>
#include <TestGame/Include/Entity/ProjectileEntity.h>
#include <TestGame/Include/Entity/AnimationEntity.h>
#include <TestGame/Include/Sound/FMODHandler.h>
#include <TestGame/Include/Sound/SoundHandler.h>
#include <TestGame/Include/Node.h>

// Custom lib include


// c++ includes
#include <fstream>
#include <random>

namespace //Used for the scripting
{
	GameScene* a_gameScene = nullptr;
}

static int CreateEnemy(lua_State* p_luaState) // float x, float y 0-39, 0-39
{
	float l_positionX, l_positionY;
	float l_width, l_height;
	float l_rotation;

	l_positionX = lua_tonumber(p_luaState, 1);
	l_positionY = lua_tonumber(p_luaState, 2);

	l_width = lua_tonumber(p_luaState, 3); 
	l_height = lua_tonumber(p_luaState, 4);
	l_rotation = lua_tonumber(p_luaState, 5);


	int argc = lua_gettop(p_luaState);
	lua_pop(p_luaState, argc);

	if(a_gameScene != nullptr)
	{
		// Create an object
		RenderEntity* l_entity = new EnemyEntity(a_gameScene->GetLuaManager(), Point(l_positionX, l_positionY));

		l_entity->Initialize(Point(l_positionX, l_positionY), Point(l_width/2, l_height/2), Point(0.0f, 0.0f), "ball.dds", SpriteEffect::FLIP_NONE, l_width, l_height, 0.1f, l_rotation, false, Point(1.0f, 1.0f));
		a_gameScene->m_renderEntities.push_back(l_entity);
	//	a_gameScene->m_collisionEntities.push_back(static_cast<CollisionEntity*>(l_entity));
		a_gameScene->m_enemyEntities.push_back(static_cast<EnemyEntity*>(l_entity));
	}
	return 0;
}


GameScene::GameScene(float width, float height)
	: m_luaManager(nullptr)
{ 
	a_gameScene = this;
	m_renderEntities		= std::vector<RenderEntity*>();
	m_enemyEntities			= std::vector<EnemyEntity*>();
	m_projectileEntities	= std::vector<ProjectileEntity*>();
	m_animationEntities		= std::vector<AnimationEntity*>();
	m_collisionEntities		= std::vector<CollisionEntity*>();
	m_width = width;
	m_height = height;
	m_spawnTimer = 0;
	m_maxEnemies = 100;
	m_life = 3;

	m_luaManager = new LuaManager();
	m_luaState = m_luaManager->GetLuaState();

	m_luaManager->RegisterFunction("CreateEnemy", CreateEnemy);
	luaL_dofile(m_luaState, "Move.lua");
}

GameScene::~GameScene()
{
}

void GameScene::Initialize(SceneManagerInterface* p_sceneManagerInterface, Jamgine::JamgineEngine* p_engine)
{
	using namespace Jamgine;
	BaseScene::Initialize(p_sceneManagerInterface, p_engine);
	
	m_soundHandler = new SoundHandler();
//	m_soundHandler->AddSource("22 - Wind.flac");
//	m_soundHandler->PlaySoundCustom();

	m_camera = Jamgine::Camera(0,0);

	playerEntity = new PlayerEntity();
	playerEntity->Initialize(Point(375.0f, 100.0f), Point(25.0f, 25.0f), Point(0.0f, 0.0f), "SpaceShip.dds", SpriteEffect::FLIP_NONE, 50.0f, 50.0f, 0.1f, 0.0f, true, Point(1.0f, 1.0f));
	
	for(int i = 0; i < m_life; i++)
	{
		AnimationEntity* b = new AnimationEntity();
		b->Initialize(Point(10+ 75*i, 740), Point(25.0f, 25.0f), Point(0.0f, 0.0f), "SpaceShip.dds", SpriteEffect::FLIP_NONE, 50.0f, 50.0f, 0.1f, 0.0f, true, Point(1.0f, 1.0f));
		m_animationEntities.push_back(b);
	}

//	LoadCurrentSetup("Level.lvl");
}

#include <exception>
void GameScene::Update(double p_deltaTime, float p_mousePositionX, float p_mousePositionY, bool p_lMouseClicked)
{
	playerEntity->Update(p_deltaTime);
	for(int i = 0; i < m_enemyEntities.size(); i++ )
		m_enemyEntities[i]->Update(p_deltaTime);

	for(int i = 0; i < m_collisionEntities.size(); i++ )
		m_collisionEntities[i]->Update(p_deltaTime);

	if(m_spawnTimer > 400)
	{
		if(m_maxEnemies > m_enemyEntities.size())
		{
	//		if(rand() % 100 > 10)
	//		{
				lua_getglobal(m_luaState, "SpawnEnemy");
				lua_call(m_luaState, 0, 0);
				m_spawnTimer = 0;
	//		}
		}
	}
	else
		m_spawnTimer++;

	Jamgine::Rectangle l_rectangle = playerEntity->GetRectangle();
	for(int i = 0; i < m_enemyEntities.size(); i++)
	{
		if(l_rectangle.Intersect(m_enemyEntities[i]->GetRectangle()))
		{
			playerEntity->RestToSpawn();
			m_life--;
			if(m_life == 0)
				m_sceneManagerInterface->NotifyExit();
		}
	}


	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		m_collisionEntities.push_back(playerEntity->CreateProjectile());
	}


	try
	{
	for ( auto i = m_collisionEntities.begin(); i != m_collisionEntities.end(); )
	{
		for ( auto j= m_enemyEntities.begin(); j != m_enemyEntities.end(); )
		{
			if( (*i)->GetRectangle().Intersect((*j)->GetRectangle()))
			{
 				delete *i; 
				delete *j;
				i = m_collisionEntities.erase(i);
				j = m_enemyEntities.erase(j);
			}
			else
			{
				++j;
			}
		}
		++i;
	}
	}
	catch(std::exception e)
	{

	}


	for ( auto it = m_enemyEntities.begin(); it != m_enemyEntities.end(); )
	{
		if( (*it)->OutsideBounds(0,800,0,800))
		{
			delete * it;  
			it = m_enemyEntities.erase(it);
		}
		else
		{
			++it;
		}
	}

	for ( auto it = m_collisionEntities.begin(); it != m_collisionEntities.end(); )
	{
		if( (*it)->OutsideBounds(0,800,0,800))
		{
			delete * it;  
			it = m_collisionEntities.erase(it);
		}
		else
		{
			++it;
		}
	}
	
}

void GameScene::CheckCollision()
{
	
}

void GameScene::Render()
{
	playerEntity->Render();

	for(int i = 0; i < m_enemyEntities.size(); i++ )
		m_enemyEntities[i]->Render();

	for(int i = 0; i < m_collisionEntities.size(); i++ )
		m_collisionEntities[i]->Render();

	for(int i = 0; i < m_life; i++)
	{
		m_animationEntities[i]->Render();
	}
	
	m_engine->PostRender(&m_camera);
}


void GameScene::SaveCurrentSetup(char* p_fileName)
{
	using namespace std;

	ofstream l_file;
	l_file.open(p_fileName);

	for (unsigned int i = 0; i < m_renderEntities.size(); i++)
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
	//	l_entity = new EnemyEntity(m_luaManager);
	//	m_enemyEntities.push_back(static_cast<EnemyEntity*>(l_entity));
	}
	else if (l_entityType == (int)ENTITY::PLAYER)
	{
		ExitProcess(0);		// This should not happen
	}
	else if (l_entityType == (int)ENTITY::PROJECTILE)
	{
		l_entity = new ProjectileEntity();
		m_projectileEntities.push_back(static_cast<ProjectileEntity*>(l_entity));
	}
	
	l_entity->LoadClassFromData(l_data);
		
	m_renderEntities.push_back(l_entity);
}
