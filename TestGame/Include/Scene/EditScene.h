#pragma once

#include <TestGame/Include/Scene/BaseScene.h>

class GameEntity;
class RenderEntity;

#include <vector>

enum class CURRENTTOOL
{
	NEWRECT,
	ENTITY,
	TEX,
	ORIGIN,
	SPRITEEFF,
	POS,
	EDITRECT,
	DEPTH,
	ROTATION,
	SUBIMG,
	TRANSPARANT
};

class EditScene : public BaseScene
{
public:
	EditScene();
	virtual ~EditScene();


	virtual void Initialize(SceneManagerInterface* p_sceneManagerInteface, Jamgine::JamgineEngine* p_engine);
	virtual void Update(double p_deltaTime, float p_mousePositionX, float p_mousePositionY, bool p_mouseClicked);
	void Render();


private:
	std::vector<RenderEntity*>		m_renderEntity;
	std::vector<RenderEntity*>		m_editSpecific;
	std::vector<Jamgine::Texture2DInterface*>	m_texture;

	int m_currentSprite;


	Jamgine::Camera m_camera;

	void SaveCurrentSetup(char* p_filename);
	void LoadCurrentSetup(char* p_filename);

	bool m_prevMouseClick;
	bool m_creatingBox;
	Jamgine::Position m_firstPos;
	Jamgine::Position m_secondPos;

	CURRENTTOOL m_currTool;

	void NewRect(float p_mousePositionX, float p_mousePositionY, bool p_mouseClicked);
	void Entity();
	void ChoseTex();
	void SetOrigin(float p_mousePositionX, float p_mousePositionY, bool p_mouseClicked);
	void SetSpriteEffect();
	void EditRect();
	void SetDepth();
	void SetRotation();
	void AmountSubImg();
	void SetTransparant();

	bool Q, W, E, R, T, Y, U, I, O, P, S, L;
	bool tab, prevtab;
	

	void PrintDebug(char* p_message);
	void PrintDebugWithValue(char* p_message, float p_value1, float p_value2, float p_value3);
	void UpdateCurrentTool();

};