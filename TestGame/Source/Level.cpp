#include <TestGame/Include/Level.h>
#include <Jamgine/Include/JWinResourceManager.h>
#include <Jamgine/Include/JDXTextureConverter.h>
#include <TestGame/Include/Entity/RenderEntity.h>
#include <Jamgine/Include/DirectX/JDirectXTexture2D.h>

Level::Level(Jamgine::JResourceManager* p_resourceManager, Jamgine::JamgineEngine* p_engine)
	: m_requiredFiles(nullptr), m_resourceManager(nullptr), m_engine(nullptr)
{
	m_resourceManager = p_resourceManager;
	m_engine = p_engine;

	m_requiredFiles = new std::string[5];
	m_requiredFiles[0] = "SpaceShip.dds";
	m_requiredFiles[1] = "SQUARE.dds";
	m_requiredFiles[2] = "Box1.dds";
	m_requiredFiles[3] = "Circle.dds";
	m_requiredFiles[4] = "ball.dds";

	for(unsigned int i = 0; i < 5; i++) //Start load of textures for the "level"
	{
		//m_resourceManager->LoadResource("Multi.zip", Jamgine::LifeTime::LEVEL, m_requiredFiles[i], Jamgine::ResourceType::TEXTURE);
		m_resourceManager->LoadResource("test.tejp", Jamgine::LifeTime::LEVEL, m_requiredFiles[i], Jamgine::ResourceType::TEXTURE);
	}
	
	
}

Level::~Level()
{
	for (unsigned int i = 0; i < m_entity.size(); ++i)
	{
		delete m_entity[i];
	}

	m_entity.clear();
	delete[] m_requiredFiles;

}

void Level::Init(unsigned int p_level)
{
	if (p_level % 2 == 0) //Level 1,3,5 etc init
	{
		for (unsigned int y = 0; y < 5; ++y)
		{
			for (unsigned int x = 0; x < 5; ++x)
			{
				RenderEntity* temp = new RenderEntity();
				Texture2DInterface* aTexture = new Texture2D();
				aTexture->LoadTexture(m_resourceManager->GetResource(m_requiredFiles[x % 5], Jamgine::LifeTime::LEVEL));
				temp->Initialize(Jamgine::Rectangle(x*35.0f, y*35.0f, 35.0f, 35.0f), aTexture, m_engine);
				m_entity.push_back(temp);
			}
		}
	}
	else //level 2,4,6 etc init
	{
		for (unsigned int y = 0; y < 5; ++y)
		{
			for (unsigned int x = 0; x < 5; ++x)
			{
				RenderEntity* temp = new RenderEntity();
				Texture2DInterface* aTexture = new Texture2D();
				aTexture->LoadTexture(m_resourceManager->GetResource(m_requiredFiles[y % 5], Jamgine::LifeTime::LEVEL));
				temp->Initialize(Jamgine::Rectangle(x*50.0f, y*50.0f, 50.0f, 50.0f), aTexture, m_engine);
				m_entity.push_back(temp);
			}
		}
	}
}

void Level::Update(double p_deltaTime)
{
	for(unsigned int i = 0; i < m_entity.size(); ++i)
	{
		m_entity.at(i)->Update(p_deltaTime);
	}
	m_resourceManager->Update();
	
}

void Level::Render()
{
	for(unsigned int i = 0; i < m_entity.size(); ++i)
	{
		m_entity.at(i)->Render();
	}
}