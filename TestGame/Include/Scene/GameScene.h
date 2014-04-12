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


	virtual void Initialize(SceneManagerInterface* p_sceneManagerInteface, Jamgine::JamgineEngine* p_engine);
	void Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked);
	void Render();

private:
	std::vector<GameEntity*>		m_gameEntity;
	std::vector<RenderEntity*>		m_renderEntity;

	Jamgine::Camera m_camera;
	Jamgine::Texture2DInterface* a;
	Jamgine::Texture2DInterface* b;
	Jamgine::Texture2DInterface* c;
	Jamgine::Texture2DInterface* d;
	Jamgine::Texture2DInterface* e;
};