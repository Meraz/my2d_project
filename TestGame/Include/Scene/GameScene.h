#pragma once

#include <TestGame/Include/Scene/BaseScene.h>

class GameEntity;
class RenderEntity;

#include <vector>

class GameScene : public BaseScene
{
public:
	GameScene();
	virtual ~GameScene();

	virtual void Initialize(SceneManagerInterface* p_sceneManagerInteface);
	void Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked);
	void Render();

private:
	std::vector<GameEntity*>		m_gameEntity;
	std::vector<RenderEntity*>		m_renderEntity;

//	std::vector<CollisionEntity*>	RenderEntity;
};