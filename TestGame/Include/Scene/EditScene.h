#pragma once

#include <TestGame/Include/Scene/BaseScene.h>

class GameEntity;
class RenderEntity;

#include <vector>
#include <Windows.h>

#define MAX_SUB_IMAGES 32

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
	TRANSPARANT,
	SELECT
};

class EditScene : public BaseScene
{
public:
	EditScene(HWND p_handle);
	virtual ~EditScene();


	virtual void Initialize(SceneManagerInterface* p_sceneManagerInteface, Jamgine::JamgineEngine* p_engine);
	virtual void Update(double p_deltaTime, float p_mousePositionX, float p_mousePositionY, bool p_mouseClicked);
	void Render();


private:
	std::vector<RenderEntity*>	m_renderEntity;
	std::vector<Jamgine::Texture2DInterface*>	m_texture;
	HWND m_handle = nullptr;
	int m_currentSprite;
	float m_depthStep;
	int m_totalTextures;
	int m_selectedSpriteVibrateTimer;
	bool m_newSpriteSelected;
	Jamgine::Position m_originalSpritePosition;


	Jamgine::Camera m_camera;

	void SaveCurrentSetup(char* p_filename);
	void LoadCurrentSetup(char* p_filename);

	bool m_prevMouseClick;
	bool m_creatingBox, editBox;
	Jamgine::Position m_firstPos;
	Jamgine::Position m_secondPos;

	CURRENTTOOL m_currTool;

	void NewRect(float p_mousePositionX, float p_mousePositionY, bool p_mouseClicked);
	void Entity();
	void ChoseTex();
	void SetOrigin(float p_mousePositionX, float p_mousePositionY, bool p_mouseClicked);
	void SetSpriteEffect();
	void EditRect(float p_mousePositionX, float p_mousePositionY, bool p_mouseClicked);	
	void SetDepth(bool p_mouseClicked);
	void SetRotation();
	void AmountSubImg(float p_mousePositionX, float p_mousePositionY, bool p_mouseClicked);
	void SetTransparant();
	void SelectSprite();

	bool Q, W, E, R, T, Y, U, I, O, P, S, L, A;
	bool tab, prevtab;
	bool m_changeXAmountSubImage;

	void PrintDebug(char* p_message);
	void PrintDebugWithValue(char* p_message, float p_value1, float p_value2, float p_value3);
	void UpdateCurrentTool();
};