#pragma once

#include <TestGame/Include/Scene/BaseScene.h>

class GameEntity;
class RenderEntity;

#include <vector>

class EditScene : public BaseScene
{
public:
	EditScene();
	virtual ~EditScene();


	virtual void Initialize(SceneManagerInterface* p_sceneManagerInteface, Jamgine::JamgineEngine* p_engine);
	void Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_lMouseClicked);
	void Render();

private:
	std::vector<RenderEntity*>		m_renderEntity;
	std::vector<RenderEntity*>		m_editSpecific;

	Jamgine::Camera m_camera;

	void SaveCurrentSetup(char* p_filename);
	void LoadCurrentSetup(char* p_filename);

	bool m_prevMouseClick;
	bool m_creatingBox;
	Jamgine::Position m_firstPos;
	Jamgine::Position m_secondPos;
};