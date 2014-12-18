#include <TestGame/Include/Scene/GameScene.h>

// Definition of forward declaration
#include <TestGame/Include/Entity/RenderEntity.h>

// c++ includes

// Jamgine includes
#include <Jamgine/Include/DirectX/JDirectXTexture2D.h>

// Others


GameScene::GameScene(float width, float height)	// TODO, save width and height
{ 
	m_renderEntities = std::vector<RenderEntity*>();
}

GameScene::~GameScene()
{
}

void GameScene::Initialize(SceneManagerInterface* p_sceneManagerInterface, Jamgine::JamgineEngine* p_engine)
{
	using namespace Jamgine;
	BaseScene::Initialize(p_sceneManagerInterface, p_engine);


	Jamgine::Texture2DInterface* a;
	m_engine->LoadTexture(&a, "Alpha.dds");
	for (unsigned int i = 0; i < 2; i++)
	{
		m_renderEntities.push_back(new RenderEntity());

	}
	m_renderEntities.at(1)->Initialize(Jamgine::Rectangle(-50.0f, -50.0f, 100.0f, 100.0f), a, m_engine);
	m_renderEntities.at(0)->Initialize(Jamgine::Rectangle(0.0f, 0.0f, 400.0f, 400.0f), a, m_engine);
	//	m_renderEntities.at(1)->Initialize(Jamgine::Rectangle(100.0f, 100.0f, 800.0f, 800.0f), a, m_engine);
	//	m_renderEntities.at(2)->Initialize(Jamgine::Rectangle(200.0f, 200.0f, 800.0f, 800.0f), a, m_engine);
	//	m_renderEntities.at(3)->Initialize(Jamgine::Rectangle(300.0f, 300.0f, 800.0f, 800.0f), a, m_engine);

}

void GameScene::Update(double p_deltaTime, float p_mousePositionX, float p_mousePositionY, bool p_lMouseClicked)
{
	for(unsigned int i = 0; i < m_renderEntities.size(); ++i)
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