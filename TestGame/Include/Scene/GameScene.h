#pragma once

#include <TestGame/Include/Scene/BaseScene.h>

class RenderEntity;
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
	std::vector<RenderEntity*>	m_renderEntities;

	Jamgine::CameraStruct m_camera;
	void SaveCurrentSetup(char* p_filename);
	void LoadCurrentSetup(char* p_filename);

	RenderEntity* playerEntity;
	
	void CheckCollision();
	void CreateObject(int l_entity, char* l_data);

	float m_width;
	float m_height;
	float m_spawnTimer;
	int m_maxEnemies;
	int m_life;
	
	Node* m_quadTreeRootNode;
};