#include <TestGame/Include/Scene/BaseScene.h>

BaseScene::BaseScene()
	: m_previousMouseState(false), m_sceneState(SceneState::MAIN_MENU), m_sceneManagerInterface(nullptr)
{

}

BaseScene::~BaseScene()
{

}

void BaseScene::Initialize(SceneManagerInterface* p_sceneManagerInterface)
{
	m_sceneManagerInterface = p_sceneManagerInterface;
}