#include <TestGame/Include/Scene/GameScene.h>

// Definition of forward declaration
#include <TestGame/Include/Entity/RenderEntity.h>
#include <TestGame/Include/Sound/FMODHandler.h>

// Custom lib include

// c++ includes
#include <fstream>

GameScene::GameScene(float width, float height)
	: m_quadTreeRootNode(nullptr)
{ 
	m_renderEntities		= std::vector<RenderEntity*>();
	m_width = width;
	m_height = height;

}

GameScene::~GameScene()
{

}

void GameScene::Initialize(SceneManagerInterface* p_sceneManagerInterface, Jamgine::JamgineEngine* p_engine)
{
	using namespace Jamgine;
	BaseScene::Initialize(p_sceneManagerInterface, p_engine);


	Jamgine::Texture2DInterface* a;
	m_engine->LoadTexture(&a, "SQUARE.dds");
	for (unsigned int i = 0; i < 2; i++)
	{
		m_renderEntities.push_back(new RenderEntity());

	}
	{
		m_renderEntities.at(1)->Initialize(Jamgine::Rectangle(-50.0f, -50.0f, 100.0f, 100.0f), a, m_engine);
		m_renderEntities.at(0)->Initialize(Jamgine::Rectangle(0.0f, 0.0f, 400.0f, 400.0f), a, m_engine);
	//	m_renderEntities.at(1)->Initialize(Jamgine::Rectangle(100.0f, 100.0f, 800.0f, 800.0f), a, m_engine);
	//	m_renderEntities.at(2)->Initialize(Jamgine::Rectangle(200.0f, 200.0f, 800.0f, 800.0f), a, m_engine);
	//	m_renderEntities.at(3)->Initialize(Jamgine::Rectangle(300.0f, 300.0f, 800.0f, 800.0f), a, m_engine);		
	}
}

void GameScene::Update(double p_deltaTime, float p_mousePositionX, float p_mousePositionY, bool p_lMouseClicked)
{
	for (unsigned int i = 0; i < m_renderEntities.size(); ++i)
	{
		//m_renderEntities.at(i)->Update(p_deltaTime);
	}
}


void GameScene::Render()
{
	for (unsigned int i = 0; i < m_renderEntities.size(); ++i)
	{
		m_renderEntities.at(i)->Render();
	}
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
