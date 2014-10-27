#include <TestGame/Include/Scene/GameScene.h>

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

	m_engine->GetResourceManager()->Init(sizeof(int)* 100, sizeof(int)* 10000000, sizeof(int)*100);

	m_currentLevelNumber = 0;

	m_currentLevel = new Level(m_engine->GetResourceManager(), m_currentLevelNumber++, m_engine);
	m_engine->GetResourceManager()->SwapLevelBuffers();
	
}

#include <Windows.h>
void GameScene::Update(double p_deltaTime, float p_mousePositionX, float p_mousePositionY, bool p_lMouseClicked)
{
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
	m_currentLevel->Update(p_deltaTime);
}

void GameScene::Render()
{
	m_currentLevel->Render();
	m_engine->PostRender();
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
