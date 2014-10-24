#include <TestGame/Include/Level.h>
#include <Jamgine/Include/JWinResourceManager.h>
#include <Jamgine/Include/JDXTextureConverter.h>
#include <TestGame/Include/Entity/RenderEntity.h>
#include <Jamgine/Include/DirectX/JDirectXTexture2D.h>

Level::Level(Jamgine::JResourceManager* p_resourceManager, unsigned int p_level, Jamgine::JamgineEngine* p_engine)
	: m_requiredFiles(nullptr), m_resourceManager(nullptr), m_engine(nullptr)
{
	m_resourceManager = p_resourceManager;
	m_engine = p_engine;
	if(p_level == 0)
	{
		m_requiredFiles = new std::string[5];
		m_requiredFiles[0] = "SpaceShip.dds";
		m_requiredFiles[1] = "Ball1.dds";
		m_requiredFiles[2] = "Ball2.dds";
		m_requiredFiles[3] = "Ball3.dds";
		m_requiredFiles[4] = "Ball4.dds";

	//	for(unsigned int i = 0; i < 5; i++)
		{
			//m_resourceManager->LoadResource("Multi.zip", Jamgine::LifeTime::LEVEL, m_requiredFiles[0], Jamgine::ResourceType::TEXTURE);
			m_resourceManager->LoadResource("test.tejp", Jamgine::LifeTime::LEVEL, m_requiredFiles[0], Jamgine::ResourceType::TEXTURE);
		}
	
		for(unsigned int y = 0; y < 10; ++y)
		{
			for(unsigned int x = 0; x < 10; ++x)
			{	
				RenderEntity* temp = new RenderEntity();
				using namespace Jamgine;
				Texture2DInterface* aTexture = new Texture2D();
				aTexture->LoadTexture(m_resourceManager->GetResource(m_requiredFiles[0]));
				temp->Initialize(Jamgine::Rectangle(x*10.0f, y*10.0f, 50.0f, 50.0f), aTexture, m_engine);
				m_entity.push_back(temp);
			}
		}
	}
	else if (p_level == 1) 
	{

	}
}

Level::~Level()
{

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