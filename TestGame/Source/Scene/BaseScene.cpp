#include <TestGame/Include/Scene/BaseScene.h>

BaseScene::BaseScene()
	:	m_previousMouseState(false),
		m_sceneState(SceneState::UNKNOWN),
		m_sceneManagerInterface(nullptr)
{

}

BaseScene::~BaseScene()
{

}

void BaseScene::Initialize(SceneManagerInterface* p_sceneManagerInterface, Jamgine::JamgineEngine* p_engine)
{
	m_sceneManagerInterface = p_sceneManagerInterface;
	m_engine = p_engine;
}