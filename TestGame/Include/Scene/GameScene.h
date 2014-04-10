#ifndef BASESCENE_H
#define BASESCENE_H

#include <TestGame/Include/Scene/BaseScene.h>

class GameScene : public BaseScene
{
public:
	GameScene();
	virtual ~GameScene();

	void Initialize();
	void Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked);
	void Render();
};

#endif