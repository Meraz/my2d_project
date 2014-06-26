#include <TestGame/Include/Scene/GameScene.h>

// Definition of forward declaration
#include <TestGame/Include/Entity/RenderEntity.h>
#include <TestGame/Include/Sound/FMODHandler.h>
#include <TestGame/Include/Node.h>

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

	m_camera = Jamgine::Camera(0,0);

	playerEntity = new RenderEntity();
	Jamgine::Texture2DInterface* a;
	m_engine->LoadTexture(&a, "Circle.dds");
	playerEntity->Initialize(Jamgine::Rectangle(0,0,50,50), a, m_engine);
	
	//	LoadCurrentSetup("Level.lvl");
}

void GameScene::Update(double p_deltaTime, float p_mousePositionX, float p_mousePositionY, bool p_lMouseClicked)
{
	for (unsigned int i = 0; i < m_renderEntities.size(); ++i)
	{
		m_renderEntities.at(i)->Update(p_deltaTime);
	}
}


void GameScene::Render()
{
	for (unsigned int i = 0; i < m_renderEntities.size(); ++i)
	{
		m_renderEntities.at(i)->Render();
	}
	playerEntity->Render(); 
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
	l_entity->LoadClassFromData(l_data);
		
	m_renderEntities.push_back(l_entity);
}
