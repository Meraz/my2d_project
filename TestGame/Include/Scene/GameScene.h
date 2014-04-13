#pragma once

#include <TestGame/Include/Scene/BaseScene.h>



class RenderEntity;
class EnemyEntity;
class ProjectileEntity;
class AnimationEntity;
class PlayerEntity;
class CollisionEntity;

#include <vector>


class GameScene : public BaseScene
{
public:
	GameScene();
	virtual ~GameScene();


	virtual void Initialize(SceneManagerInterface* p_sceneManagerInteface, Jamgine::JamgineEngine* p_engine);
	void Update(double p_deltaTime, float p_mousePositionX, float p_mousePositionY, bool p_lMouseClicked);
	void Render();

private:
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

	PlayerEntity* player;


	void CheckCollision();
	bool GameScene::InScreen(CollisionEntity* entity);
};