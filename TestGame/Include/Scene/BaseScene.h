#ifndef BASESCENE_H
#define BASESCENE_H

#include <TestGame\Include\Scene\SceneState.h>

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();

	virtual void Initialize();
	virtual void Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked) = 0;
	virtual void Render() = 0;

protected:
	SceneState::State m_sceneState;
	bool m_previousMouseState;

};

#endif