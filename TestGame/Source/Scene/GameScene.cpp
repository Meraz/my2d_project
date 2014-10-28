#include <TestGame/Include/Scene/GameScene.h>
#include <Jamgine/Include/DirectX/JDirectXTexture2D.h>

#include <Windows.h>
// Definition of forward declaration
#include <TestGame/Include/Entity/RenderEntity.h>

// Custom lib include

// c++ includes
#include <fstream>

GameScene::GameScene(float width, float height)
	:	m_quadTreeRootNode(nullptr),
		m_currentLevel(nullptr)
{ 
//	m_renderEntities		= std::vector<RenderEntity*>();
	m_width = width;
	m_height = height;
}

GameScene::~GameScene()
{
	delete m_currentLevel;
}

void GameScene::Initialize(SceneManagerInterface* p_sceneManagerInterface, Jamgine::JamgineEngine* p_engine)
{
	using namespace Jamgine;
	BaseScene::Initialize(p_sceneManagerInterface, p_engine);

	m_engine->GetResourceManager()->Init(sizeof(int)* 10000000, sizeof(int)* 10000000, sizeof(int)* 1000000);

	InitGlobalStuff();

	m_currentLevelNumber = 0;

	m_currentLevel = new Level(m_engine->GetResourceManager(), m_currentLevelNumber++, m_engine);
	m_engine->GetResourceManager()->SwapLevelBuffers();
	
}

void GameScene::InitGlobalStuff()
{
	std::string name = "Player.dds";
	m_engine->GetResourceManager()->LoadResource("Multi.zip", Jamgine::LifeTime::GLOBAL, name, Jamgine::ResourceType::TEXTURE);
	m_playerEntity = new RenderEntity();
	Texture2DInterface* aTexture = new Texture2D();
	aTexture->LoadTexture(m_engine->GetResourceManager()->GetResource(name));
	m_playerEntity->Initialize(Jamgine::Rectangle(-35.0f, -35.0f, 75.0f, 75.0f), aTexture, m_engine);
}

void GameScene::Update(double p_deltaTime, float p_mousePositionX, float p_mousePositionY, bool p_lMouseClicked)
{
	//Next level shit
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if (m_nextButtonWasClicked == false)
		{
			delete m_currentLevel;
			m_currentLevel = new Level(m_engine->GetResourceManager(), m_currentLevelNumber++, m_engine);
			m_engine->GetResourceManager()->SwapLevelBuffers();
		}
		m_nextButtonWasClicked = true;
	}
	else
	{
		m_nextButtonWasClicked = false;
	}

	//Event stuff
	float eventTime = 1.0f;
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (m_eventButtonClicked == false)
		{
			StartEvent();
			m_eventTimer = eventTime;
		}
		m_eventButtonClicked = true;
	}
	else
	{
		m_eventButtonClicked = false;
		if (m_eventTimer >= 0.0f)
		{
			m_eventTimer -= p_deltaTime;
			if (m_eventTimer <= 0.0f)
			{
				for (auto i : m_eventities)
				{
					delete i;
				}
				m_eventities.clear();
				m_engine->GetResourceManager()->WipeResourceStack(Jamgine::LifeTime::EVENT);
			}
		}
	}
	for (auto i : m_eventities)
	{
		int test = rand();
		if (test%4 == 0)
			i->m_rectangle.position.x += 200.0f * p_deltaTime;
		else if (test%4 == 1)
			i->m_rectangle.position.x -= 200.0f * p_deltaTime;
		else if (test % 4 == 2)
			i->m_rectangle.position.y += 200.0f * p_deltaTime;
		else if (test % 4 == 3)
			i->m_rectangle.position.y -= 200.0f * p_deltaTime;
	}
		
	
	//Player update
	float speed = 500.0f;
	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_playerEntity->m_rectangle.position.y += speed*p_deltaTime;
		//m_playerEntity->m_position.y += speed*p_deltaTime;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_playerEntity->m_rectangle.position.x -= speed*p_deltaTime;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_playerEntity->m_rectangle.position.y -= speed*p_deltaTime;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_playerEntity->m_rectangle.position.x += speed*p_deltaTime;
	}
	m_currentLevel->Update(p_deltaTime);
}

void GameScene::Render()
{
	for (auto i : m_eventities)
	{
		i->Render();
	}
	m_playerEntity->Render();
	m_currentLevel->Render();
	m_engine->PostRender();
}

void GameScene::StartEvent()
{
	//Clear event stack here
	
	std::string name = "pow.dds";
	m_engine->GetResourceManager()->LoadResource("Multi.zip", Jamgine::LifeTime::EVENT, name, Jamgine::ResourceType::TEXTURE);
	RenderEntity* temp = new RenderEntity();
	Texture2DInterface* aTexture = new Texture2D();
	aTexture->LoadTexture(m_engine->GetResourceManager()->GetResource(name));
	temp->Initialize(Jamgine::Rectangle(m_playerEntity->m_rectangle.position.x, m_playerEntity->m_rectangle.position.y, 75.0f, 75.0f), aTexture, m_engine);
	m_eventities.push_back(temp); //Lol => Lots of Leaks
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
	l_entity->LoadClassFromData(l_data);
		
	m_renderEntities.push_back(l_entity);
}
