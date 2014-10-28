#pragma once

#include <TestGame/Include/Scene/BaseScene.h>
#include <TestGame/Include/Level.h>

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

	void SaveCurrentSetup(char* p_filename);
	void LoadCurrentSetup(char* p_filename);

	void InitGlobalStuff();
	void StartEvent();
	RenderEntity* m_playerEntity;

	bool m_eventButtonClicked;
	float m_eventTimer;
	std::vector<RenderEntity*> m_eventities;
	
	void CheckCollision();
	void CreateObject(int l_entity, char* l_data);

	float m_width;
	float m_height;
	float m_spawnTimer;
	int m_maxEnemies;
	int m_life;
	
	Node* m_quadTreeRootNode;

	Level* m_currentLevel;
	Level* m_nextLevel;
	
	bool m_nextButtonWasClicked;
	int m_currentLevelNumber;
};