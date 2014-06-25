#pragma once

#include <TestGame/Include/Scene/BaseScene.h>

class RenderEntity;
class EnemyEntity;
class ProjectileEntity;
class AnimationEntity;
class PlayerEntity;
class CollisionEntity;
class Node;

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
	
	bool initialized;
public:
	std::vector<EnemyEntity*>		m_enemyEntities;
	std::vector<ProjectileEntity*>  m_projectileEntities;
	std::vector<AnimationEntity*>	m_animationEntities;
	std::vector<CollisionEntity*>	m_collisionEntities;
	std::vector<RenderEntity*>		m_renderEntities;
private:
	Jamgine::Camera m_camera;
	void SaveCurrentSetup(char* p_filename);
	void LoadCurrentSetup(char* p_filename);

	PlayerEntity* playerEntity;
	
	void CheckCollision();
	bool InScreen(CollisionEntity* entity);
	void CreateObject(int l_entity, char* l_data);


	std::vector<RenderEntity*>		m_renderEntities;

	float m_width;
	float m_height;
	float m_spawnTimer;
	int m_maxEnemies;
	int m_life;
	
	Node* m_quadTreeRootNode;

};