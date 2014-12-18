#pragma once

#include <TestGame/Include/Scene/BaseScene.h>
#include <TestGame/Include/Entity/RenderEntity.h>
#include <vector>

class GameScene : public BaseScene
{
public:
	GameScene(float width, float height);
	virtual ~GameScene();
	
	virtual void Initialize(SceneManagerInterface* p_sceneManagerInteface, Jamgine::JamgineEngine* p_engine);
	void Update(double p_deltaTime, float p_mousePositionX, float p_mousePositionY, bool p_lMouseClicked);
	void Render();

private:
	std::vector<RenderEntity*>	m_renderEntities;
};