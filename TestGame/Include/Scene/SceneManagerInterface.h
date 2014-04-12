#pragma once

#include <TestGame/Include/Scene/SceneState.h>	

class SceneManagerInterface
{
public:
	virtual void SwapSceneState(SceneState p_sceneState) = 0;
	virtual void NotifyExit() = 0;
};