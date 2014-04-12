#pragma once

#include <TestGame/Include/Scene/BaseScene.h>

class MainMenuScene : public BaseScene
{
public:
	MainMenuScene();
	virtual ~MainMenuScene();

	int i;
	virtual void Initialize(SceneManagerInterface* p_sceneManagerInteface);
	void Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked);
	void Render();
};