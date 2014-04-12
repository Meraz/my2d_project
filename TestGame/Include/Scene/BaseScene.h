#pragma once

#include <Jamgine/Include/Jamgine.h>

#include <TestGame/Include/Scene/SceneState.h>

#include <TestGame/Include/Scene/SceneManagerInterface.h>

#include <TestGame/Include/XBOXController.h>

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();	

	virtual void Initialize(SceneManagerInterface* p_sceneManagerInteface, Jamgine::JamgineEngine* p_engine);
	virtual void Update(double p_deltaTime, float p_mousePositionX, float p_mousePositionY, bool p_lMouseClicked) = 0;
	virtual void Render() = 0;

protected:
	SceneState m_sceneState;
	bool m_previousMouseState;
	SceneManagerInterface* m_sceneManagerInterface;
	Jamgine::JamgineEngine* m_engine;
};