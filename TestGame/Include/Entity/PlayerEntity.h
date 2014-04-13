#ifndef PLAYERENTITY_H
#define PLAYERENTITY_H

#include <TestGame/Include/Entity/RenderEntity.h>

#include <TestGame/Include/Entity/AnimationEntity.h>
#include <TestGame/Include/XBOXController.h>
#include <vector>

#define WHALE_JUMP_VELOCITY 500
#define GOAT_JUMP_VELOCITY 750
#define MAX_X_VELOCITY 1600
#define FRICTION_X_LINEAR_SUBTRACTER 300
#define MAX_Y_VELOCITY WHALE_JUMP_VELOCITY + GOAT_JUMP_VELOCITY
#define INPUT_X_DEVIDER 10
#define GOAT_HOVER_MAX_TIME 3
#define GOAT_HOVER_COLDOWN_TIME 3

#define WHALE_JUMP_ANIMATION_TIME 0.05

struct AnimationSetup
{
	float width;
	float height;
	Texture2DInterface* texture;
	Jamgine::Position numOfSubTextures;
};

/* CHEATSHEET of animations
0 - 

*/

class PlayerEntity : public AnimationEntity
{
public:
	PlayerEntity();
	virtual ~PlayerEntity();

	virtual std::stringstream ToFile();
	virtual void LoadClassFromData(char* p_data);

	void AddAnimationTexture(float p_width, float p_height, char * p_textureName, Jamgine::Position p_numOfSubTextures);
	virtual void Update(double p_deltaTime);
	void CollideStatic();
	void Kill();

private:

	bool	m_hasWhaleJumped;
	bool	m_hasGoatBoost;
	bool	m_onGround;
	bool	m_isWhaleAnimating;;
	bool	m_isAlive;
	double  m_goatDurationTimer;
	double  m_goatJumpColdownTimer;
	double  m_animationWhaleJumpTimer;
	Jamgine::Position m_velocity;

	XBOXController* m_playerOneController;
	XBOXController* m_playerTwoController;
	
	std::vector<AnimationSetup> m_animations;

	Position lastPos;

	void CheckMovementInputs();
	void MoveSideways(float amount);
	void WhaleJump();
	void GoatJump();


	
	void  UseAnimationSetup(int p_setupIndex);

};

#endif

/*
	bool isPressed = ((m_controller->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0);

 XINPUT_GAMEPAD_DPAD_UP       
 XINPUT_GAMEPAD_DPAD_DOWN     
 XINPUT_GAMEPAD_DPAD_LEFT     
 XINPUT_GAMEPAD_DPAD_RIGHT    
 XINPUT_GAMEPAD_START         
 XINPUT_GAMEPAD_BACK          
 XINPUT_GAMEPAD_LEFT_THUMB    
 XINPUT_GAMEPAD_RIGHT_THUMB   
 XINPUT_GAMEPAD_LEFT_SHOULDER 
 XINPUT_GAMEPAD_RIGHT_SHOULDER
 XINPUT_GAMEPAD_A             
 XINPUT_GAMEPAD_B             
 XINPUT_GAMEPAD_X             
 XINPUT_GAMEPAD_Y             
*/
