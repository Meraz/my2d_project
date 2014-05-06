#pragma once

#include <TestGame/Include/Scene/BaseScene.h>



class RenderEntity;
class EnemyEntity;
class ProjectileEntity;
class AnimationEntity;
class PlayerEntity;
class CollisionEntity;
class SoundHandler;

#include <vector>
using namespace Jamgine;

class GameScene : public BaseScene
{
public:
	GameScene(float width, float height);
	virtual ~GameScene();
	
	virtual void Initialize(SceneManagerInterface* p_sceneManagerInteface, Jamgine::JamgineEngine* p_engine);
	void Update(double p_deltaTime, float p_mousePositionX, float p_mousePositionY, bool p_lMouseClicked);
	void Render();

private:
	float m_width;
	float m_height;

	std::vector<RenderEntity*>		m_renderEntities;
	std::vector<EnemyEntity*>		m_enemyEntities;
	std::vector<ProjectileEntity*>  m_projectileEntities;
	std::vector<AnimationEntity*>	m_animationEntities;
	std::vector<CollisionEntity*>	m_collisionEntities;


	Jamgine::Camera m_camera;
	Jamgine::Texture2DInterface* a;
	Jamgine::Texture2DInterface* b;
	void SaveCurrentSetup(char* p_filename);
	void LoadCurrentSetup(char* p_filename);

	std::vector<PlayerEntity*> playerEntities;



	void CheckCollision();

	bool InScreen(CollisionEntity* entity);
	int CollideBox(Point apos, float aWidth, float aHeight, Jamgine::Point bPos, float bWidth, float bHeight);
	bool HorizontalCollision(Point playPos, Point objPos, float playWidth, float playHeight, float objWidth);
	bool VerticalCollision(Point playPos, Point objPos, float playWidth, float playHeight, float objHeight);

	void CreateObject(int l_entity, char* l_data);
	SoundHandler* m_soundHandler;

};