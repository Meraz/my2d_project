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

namespace //Used for the scripting
{
	GameScene* a_gameScene = nullptr;
}

static int SetMapSize(lua_State* l_luaState) // float x, float y
{
	float width, height;
	width = lua_tonumber(l_luaState, 1);
	height = lua_tonumber(l_luaState, 2);
	int argc = lua_gettop(l_luaState);
	lua_pop(l_luaState, argc);

	a_gameScene->m_width = width;
	a_gameScene->m_height = height;

	a_gameScene->m_quadTreeRootNode = new Node(Jamgine::Rectangle(0,0,width, height));
	return 1;
}

static int AddObject(lua_State* l_luaState) // float x, float y
{
	float x, y, width, height;
	x = lua_tonumber(l_luaState, 1);
	y = lua_tonumber(l_luaState, 2);
	width = lua_tonumber(l_luaState, 3);
	height = lua_tonumber(l_luaState, 4);
	int argc = lua_gettop(l_luaState);
	lua_pop(l_luaState, argc);

	if(a_gameScene != nullptr)
	{
		CollisionEntity* l_collisionEntity = new CollisionEntity();
		l_collisionEntity->Initialize(Jamgine::Rectangle(x, y, width, height), "Circle.dds");
		a_gameScene->m_quadTreeRootNode->AddEntity(l_collisionEntity);	
	}
	return 1;
}

static int StaticCheckCollision(lua_State* l_luaState) // float x, float y, float width, float height
{
	float x, y, width, height;
	x = lua_tonumber(l_luaState, 1);
	y = lua_tonumber(l_luaState, 2);
	width = lua_tonumber(l_luaState, 3);
	height = lua_tonumber(l_luaState, 4);
	int argc = lua_gettop(l_luaState);
	lua_pop(l_luaState, argc);

	if(a_gameScene != nullptr)
		return a_gameScene->m_quadTreeRootNode->Collide(Jamgine::Rectangle(x, y, width, height));	
	return 1;
}

GameScene::GameScene(float width, float height)
	: m_quadTreeRootNode(nullptr), m_luaManager(nullptr)
{ 
	a_gameScene = this;
	m_renderEntities		= std::vector<RenderEntity*>();
	m_enemyEntities			= std::vector<EnemyEntity*>();
	m_projectileEntities	= std::vector<ProjectileEntity*>();
	m_animationEntities		= std::vector<AnimationEntity*>();
	m_collisionEntities		= std::vector<CollisionEntity*>();
	m_width = width;
	m_height = height;

	m_luaManager = new LuaManager();
	m_luaManager->RegisterFunction("SetMapSize", SetMapSize);	
	m_luaManager->RegisterFunction("StaticCheckCollision", StaticCheckCollision);
	m_luaManager->RegisterFunction("AddObject", AddObject);

//	m_luaManager->RunEntireScript("Maze1.lua");
	m_luaManager->RunSpecificFuntionInScript("Maze1.lua", "Test");
}

GameScene::~GameScene()
{
}

void GameScene::Initialize(SceneManagerInterface* p_sceneManagerInterface, Jamgine::JamgineEngine* p_engine)
{
	using namespace Jamgine;
	BaseScene::Initialize(p_sceneManagerInterface, p_engine);
	
	m_soundHandler = new SoundHandler();
	m_soundHandler->AddSource("22 - Wind.flac");
//	m_soundHandler->PlaySoundCustom();

	m_camera = Jamgine::Camera(0,0);

	playerEntity = new PlayerEntity();
	playerEntity->Initialize(Point(200.0f, 400.0f), Point(0.0f, 0.0f), Point(0.0f, 0.0f), "Circle.dds", SpriteEffect::FLIP_NONE, 250.0f, 300.0f, 0.1f, 0.0f, true, Point(1.0f, 1.0f));
	//playerEntity->Initialize(Point(200, 400), Point(0, 0), Point(0, 0), "Circle.dds", SpriteEffect::FLIP_NONE, 250, 300, 0.1, 0, true, Point(1, 1));
	
	
//	LoadCurrentSetup("Level.lvl");
}

void GameScene::Update(double p_deltaTime, float p_mousePositionX, float p_mousePositionY, bool p_lMouseClicked)
{
	playerEntity->Update(p_deltaTime);
}

void GameScene::CheckCollision()
{
	
}

void GameScene::Render()
{
	playerEntity->Render();

	m_quadTreeRootNode->Render(Jamgine::Rectangle(0, 0, m_width, m_height));

	/*
	for (unsigned int i = 0; i < m_renderEntities.size(); i++)
	{
		m_renderEntities[i]->Render(m_engine);
	}*/

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
		l_entity = new EnemyEntity();
		m_enemyEntities.push_back(static_cast<EnemyEntity*>(l_entity));
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
