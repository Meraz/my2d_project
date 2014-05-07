#pragma once

#include <TestGame/Include/Scene/BaseScene.h>

class RenderEntity;
class EnemyEntity;
class ProjectileEntity;
class AnimationEntity;
class PlayerEntity;
class CollisionEntity;
class SoundHandler;
class Node;

#include <LuaModule/Include/LuaManager.h>
//class LuaManager;

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
	
	std::vector<EnemyEntity*>		m_enemyEntities;
	std::vector<ProjectileEntity*>  m_projectileEntities;
	std::vector<AnimationEntity*>	m_animationEntities;
	std::vector<CollisionEntity*>	m_collisionEntities;

	Jamgine::Camera m_camera;
	Jamgine::Texture2DInterface* a;
	Jamgine::Texture2DInterface* b;
	SoundHandler* m_soundHandler;
	void SaveCurrentSetup(char* p_filename);
	void LoadCurrentSetup(char* p_filename);

	PlayerEntity* playerEntity;
	
	void CheckCollision();
	bool InScreen(CollisionEntity* entity);
	void CreateObject(int l_entity, char* l_data);
	LuaManager* m_luaManager;
	
public:
	std::vector<RenderEntity*>		m_renderEntities;
	CollisionEntity* m_wall[40][40];
	float m_width;
	float m_height;
	Node* m_quadTreeRootNode;

};