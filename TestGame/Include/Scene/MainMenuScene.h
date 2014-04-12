#pragma once

#include <TestGame/Include/Scene/BaseScene.h>

class MainMenuScene : public BaseScene
{
public:
	MainMenuScene();
	virtual ~MainMenuScene();

	int i;
	virtual void Initialize(SceneManagerInterface* p_sceneManagerInteface,Jamgine::JamgineEngine* p_engine);
	void Update(double p_deltaTime, float p_mousePositionX, float p_mousePositionY, bool p_lMouseClicked);
	void Render();
};