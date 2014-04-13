#include <TestGame/Include/Scene/GameScene.h>

// Definition of forward declaration
#include <TestGame/Include/Entity/RenderEntity.h>
#include <TestGame/Include/Entity/PlayerEntity.h>
#include <TestGame/Include/Entity/EnemyEntity.h>
#include <TestGame/Include/Entity/ProjectileEntity.h>
#include <TestGame/Include/Entity/AnimationEntity.h>
//#include <TestGame/Include/Sound/FMODHandler.h>
//#include <TestGame/Include/Sound/SoundHandler.h>

// c++ includes
#include <fstream>

GameScene::GameScene(float width, float height)
{ 
	m_renderEntities		= std::vector<RenderEntity*>();
	m_enemyEntities			= std::vector<EnemyEntity*>();
	m_projectileEntities	= std::vector<ProjectileEntity*>();
	m_animationEntities		= std::vector<AnimationEntity*>();
	m_collisionEntities		= std::vector<CollisionEntity*>();
	m_width = width;
	m_height = height;
}

GameScene::~GameScene()
{
}

void GameScene::Initialize(SceneManagerInterface* p_sceneManagerInterface, Jamgine::JamgineEngine* p_engine)
{
	BaseScene::Initialize(p_sceneManagerInterface, p_engine);
	
	/*m_soundHandler = new SoundHandler();
	m_soundHandler->AddSource("LionKing.wav");*/
	//m_soundHandler->PlaySoundCustom();

	m_camera = Jamgine::Camera(0,0);
	playerEntities.push_back( new PlayerEntity(0));
	playerEntities.push_back( new PlayerEntity(1));


	playerEntities[0]->Initialize(Jamgine::Position(200,400),Jamgine::Position(0,0),Jamgine::Position(0,0),"VAL_ANIMATION.dds",Jamgine::SpriteEffect::FLIP_NONE,250,300,0.1,0,true,Jamgine::Position(5,5)); //funkar med valtexture
	playerEntities[1]->Initialize(Jamgine::Position(400,400),Jamgine::Position(0,0),Jamgine::Position(0,0),"VAL_ANIMATION.dds",Jamgine::SpriteEffect::FLIP_NONE,250,300,0.1,0,true,Jamgine::Position(5,5)); //funkar med valtexture

	for (int i = 0; i < 2; i++)
	{
		m_collisionEntities.push_back(new CollisionEntity());
	}

	
	m_collisionEntities[0]->Initialize(Position(700,0),"Circle.dds",100,100);
	m_collisionEntities[1]->Initialize(Position(0,10),"Circle.dds",800,30);
	

	//LoadCurrentSetup("Level.lvl");
	

	//player->Initialize(Jamgine::Position(200,200),Jamgine::Position(0,0),Jamgine::Position(0,0),"VAL_ANIMATION.dds",Jamgine::SpriteEffect::FLIP_NONE,250,300,0.1,0,true,Jamgine::Position(5,5)); //funkar med valtexture
	//player->AddAnimationTexture(50,50,"Anim2.dds", Jamgine::Position(3,3)); //test for multiple animations

}

void GameScene::Update(double p_deltaTime, float p_mousePositionX, float p_mousePositionY, bool p_lMouseClicked)
{

	playerEntities[0]->Update(p_deltaTime);
	playerEntities[1]->Update(p_deltaTime);

	CheckCollision();

	//m_soundHandler->Update();
	/* iterate collision objects
	for(int i = 0; i < m_collisionEntity.size(); i++)
	{
		for(int j = 0; j < m_collisionEntity.size(); j++)
		{
			if(m_collisionEntity.at(j) == m_collisionEntity.at(i)){}
			else
			{
				if(collisionCheck(m_collisionEntity.at(i), m_collisionEntity.at(j)))
				{
					if(m_collisionEntity.at(i)->getType() == m_collisionEntity.at(j)->getType())
					{
						won't work, figure shiet aut
					}
				}
			}
		}
	}
	*/


}

void GameScene::CheckCollision()
{
	for (int i = 0; i < playerEntities.size(); i++)
	{
		int projCount = m_projectileEntities.size();
		for (int i = 0; i < projCount; i++)
		{
			if (InScreen(m_projectileEntities[i]))
			{
				if (CollideBox(m_projectileEntities[i]->GetPosition(),m_projectileEntities[i]->GetWidth() ,m_projectileEntities[i]->GetHeight(), playerEntities[i]->GetPosition(), playerEntities[i]->GetWidth(), playerEntities[i]->GetHeight()))
				{

				}
			}
		}

		int enemyCount = m_enemyEntities.size();
		for (int i = 0; i < enemyCount; i++)
		{
			if (InScreen(m_enemyEntities[i]))
			{
				if (CollideBox(m_enemyEntities[i]->GetPosition(),m_enemyEntities[i]->GetWidth() ,m_enemyEntities[i]->GetHeight(), playerEntities[i]->GetPosition(), playerEntities[i]->GetWidth(), playerEntities[i]->GetHeight()))
				{

				}
			}
		}

		int collCount = m_collisionEntities.size();
		for (int i = 0; i < collCount; i++)
		{
			if (InScreen(m_collisionEntities[i]))
			{
				if (CollideBox(m_collisionEntities[i]->GetPosition(),m_collisionEntities[i]->GetWidth() ,m_collisionEntities[i]->GetHeight(), playerEntities[i]->GetPosition(), playerEntities[i]->GetWidth(), playerEntities[i]->GetHeight()))
				{

					int leftTop, rightTop, leftBot, rightBot;
					float halfWidth = playerEntities[i]->GetWidth()/2;
					float halfHeight = playerEntities[i]->GetHeight()/2;
					Position pos = playerEntities[i]->GetPosition();

					leftTop = CollideBox(Position(pos.x , pos.y + halfHeight), halfWidth, halfHeight, m_collisionEntities[i]->GetPosition(), m_collisionEntities[i]->GetWidth(), m_collisionEntities[i]->GetHeight());
					rightTop = CollideBox(Position(pos.x + halfWidth, pos.y + halfHeight), halfWidth, halfHeight, m_collisionEntities[i]->GetPosition(), m_collisionEntities[i]->GetWidth(), m_collisionEntities[i]->GetHeight());
					leftBot = CollideBox(Position(pos.x , pos.y), halfWidth, halfHeight, m_collisionEntities[i]->GetPosition(), m_collisionEntities[i]->GetWidth(), m_collisionEntities[i]->GetHeight());
					rightBot = CollideBox(Position(pos.x + halfWidth, pos.y), halfWidth, halfHeight, m_collisionEntities[i]->GetPosition(), m_collisionEntities[i]->GetWidth(), m_collisionEntities[i]->GetHeight());

				
					if (leftTop + rightTop + leftBot + rightBot == 1)
					{
						playerEntities[i]->InverseCollide();
					}
					else
					{
						playerEntities[i]->JawsCollide(leftTop,rightTop,leftBot,rightBot,m_collisionEntities[i]->GetPosition().y + m_collisionEntities[i]->GetHeight(), m_collisionEntities[i]->GetPosition().y);
					}
				
				}
			}
		}
	}

	if (CollideBox(playerEntities[1]->GetPosition(),playerEntities[1]->GetWidth() ,playerEntities[1]->GetHeight(), playerEntities[0]->GetPosition(), playerEntities[0]->GetWidth(), playerEntities[0]->GetHeight()))
	{
		{
			int leftTop, rightTop, leftBot, rightBot;
			float halfWidth = playerEntities[0]->GetWidth()/2;
			float halfHeight = playerEntities[0]->GetHeight()/2;
			Position pos = playerEntities[0]->GetPosition();

			leftTop = CollideBox(Position(pos.x , pos.y + halfHeight), halfWidth, halfHeight, playerEntities[1]->GetPosition(), playerEntities[1]->GetWidth(), playerEntities[1]->GetHeight());
			rightTop = CollideBox(Position(pos.x + halfWidth, pos.y + halfHeight), halfWidth, halfHeight, playerEntities[1]->GetPosition(), playerEntities[1]->GetWidth(), playerEntities[1]->GetHeight());
			leftBot = CollideBox(Position(pos.x , pos.y), halfWidth, halfHeight, playerEntities[1]->GetPosition(), playerEntities[1]->GetWidth(), playerEntities[1]->GetHeight());
			rightBot = CollideBox(Position(pos.x + halfWidth, pos.y), halfWidth, halfHeight, playerEntities[1]->GetPosition(), playerEntities[1]->GetWidth(), playerEntities[1]->GetHeight());

				
			if (leftTop + rightTop + leftBot + rightBot == 1)
			{
				playerEntities[0]->InverseCollide();
			}
			else
			{
				playerEntities[0]->JawsCollide(leftTop,rightTop,leftBot,rightBot,m_collisionEntities[0]->GetPosition().y + m_collisionEntities[0]->GetHeight(), m_collisionEntities[0]->GetPosition().y);
			}
		}

		{
			int leftTop, rightTop, leftBot, rightBot;
			float halfWidth = playerEntities[1]->GetWidth()/2;
			float halfHeight = playerEntities[1]->GetHeight()/2;
			Position pos = playerEntities[1]->GetPosition();

			leftTop = CollideBox(Position(pos.x , pos.y + halfHeight), halfWidth, halfHeight, playerEntities[0]->GetPosition(), playerEntities[0]->GetWidth(), playerEntities[0]->GetHeight());
			rightTop = CollideBox(Position(pos.x + halfWidth, pos.y + halfHeight), halfWidth, halfHeight, playerEntities[0]->GetPosition(), playerEntities[0]->GetWidth(), playerEntities[0]->GetHeight());
			leftBot = CollideBox(Position(pos.x , pos.y), halfWidth, halfHeight, playerEntities[0]->GetPosition(), playerEntities[0]->GetWidth(), playerEntities[0]->GetHeight());
			rightBot = CollideBox(Position(pos.x + halfWidth, pos.y), halfWidth, halfHeight, playerEntities[0]->GetPosition(), playerEntities[0]->GetWidth(), playerEntities[0]->GetHeight());

				
			if (leftTop + rightTop + leftBot + rightBot == 1)
			{
				playerEntities[1]->InverseCollide();
			}
			else
			{
				playerEntities[1]->JawsCollide(leftTop,rightTop,leftBot,rightBot,m_collisionEntities[1]->GetPosition().y + m_collisionEntities[1]->GetHeight(), m_collisionEntities[1]->GetPosition().y);
			}
		}
	}
}

//
//bool GameScene::HorizontalCollision(Position playPos, Position objPos, float playWidth, float playHeight, float objWidth)
//{
//	bool intersection = false;
//
//	if (player->IsOnGround() && playPos.y < objPos.y ||  playPos.y + playHeight > objPos.y &&
//		(playPos.x + playWidth > objPos.x || playPos.x < objPos.x + objWidth))
//	{
//		intersection = true;
//		player->SetVelocityX(0);
//	}
//
//	return intersection;
//}
//bool GameScene::VerticalCollision(Position playPos, Position objPos, float playWidth, float playHeight, float objHeight)
//{
//	bool intersection = false;
//
//	if (player->IsOnGround() && playPos.x < objPos.x || playPos.x + playWidth > objPos.x &&
//		(playPos.y + playHeight > objPos.y || playPos.y < objPos.y + objHeight))
//	{
//		player->SetVelocityY(0);
//		intersection = true;
//		player->CollideStatic();
//	}
//
//	return intersection;
//}


int GameScene::CollideBox(Position aPos, float aWidth, float aHeight, Position bPos, float bWidth, float bHeight)
{
	if (aPos.x-bPos.x > 0)
	{
		if (bPos.x + bWidth > aPos.x)
		{
			if (aPos.y-bPos.y > 0)
			{
				if (bPos.y + bHeight > aPos.y)
				{
					return 1;
				}
			}
			else
			{
				if (aPos.y + aHeight > bPos.y)
				{
					return 1;
				}
			}
		}
	}
	else
	{
		if (aPos.x + aWidth > bPos.x)
		{
			if (aPos.y-bPos.y > 0)
			{
				if (bPos.y + bHeight > aPos.y)
				{
					return 1;
				}
			}
			else
			{
				if (aPos.y + aHeight > bPos.y)
				{
					return 1;
				}
			}
		}
	}
	return 0;
}


bool GameScene::InScreen(CollisionEntity* entity)
{
	Position p = entity->GetPosition();
	if (m_camera.position.x - p.x > 0) //entity is left
	{
		float width = entity->GetWidth();
		if (p.x + width > m_camera.position.x )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		float width = m_width;
		if (m_camera.position.x + width > p.x )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}



void GameScene::Render()
{

	playerEntities[0]->Render(m_engine);
	playerEntities[1]->Render(m_engine);

	for (int i = 0; i < m_collisionEntities.size(); i++)
	{
		m_collisionEntities[i]->Render(m_engine);
	}

	int max = m_renderEntities.size();
	for (unsigned int i = 0; i < max; i++)
	{
		m_renderEntities[i]->Render(m_engine);
	}

	m_engine->PostRender(&m_camera);
}


void GameScene::SaveCurrentSetup(char* p_fileName)
{
	using namespace std;

	ofstream l_file;
	l_file.open(p_fileName);

	unsigned int l_totalObjects = m_renderEntities.size();
	for (unsigned int i = 0; i < l_totalObjects; i++)
	{
		l_file << m_renderEntities[i]->ToFile().str();
		l_file << "\n";
	}
	l_file.close();
}

void GameScene::LoadCurrentSetup(char* p_fileName)
{
	using namespace std;

	ifstream l_stream;
	l_stream.open(p_fileName);

	unsigned int l_totalObjects = m_renderEntities.size();

	char l_buffer[1024];

	while (l_stream.getline(l_buffer, 1024))
	{
		char lKey[8];

		// Texture
		RenderEntity* l_renderEntity;
		sscanf_s(l_buffer, "%i ", lKey, sizeof(lKey));
		CreateObject(lKey[0], l_buffer);
	}

	l_stream.close();
}

void GameScene::CreateObject(int l_entityType, char* l_data)
{
	RenderEntity* l_entity;

	if (l_entityType == (int)ENTITY::RENDER)
	{
		l_entity = new RenderEntity();
	}
	else if (l_entityType == (int)ENTITY::COLLISION)
	{
		l_entity = new CollisionEntity();
		m_collisionEntities.push_back(static_cast<CollisionEntity*>(l_entity));
	}
	else if (l_entityType == (int)ENTITY::ANIMATION)
	{
		l_entity = new AnimationEntity();
		m_animationEntities.push_back(static_cast<AnimationEntity*>(l_entity));
	}
	else if (l_entityType == (int)ENTITY::ENENMY)
	{
		l_entity = new EnemyEntity();
		m_enemyEntities.push_back(static_cast<EnemyEntity*>(l_entity));
	}
	else if (l_entityType == (int)ENTITY::PLAYER)
	{
		ExitProcess(0);//	return; // l_entity = new RenderEntity(); // This should not happen
	}
	else if (l_entityType == (int)ENTITY::PROJECTILE)
	{
		l_entity = new ProjectileEntity();
		m_projectileEntities.push_back(static_cast<ProjectileEntity*>(l_entity));
	}
	
	l_entity->LoadClassFromData(l_data);
		
	m_renderEntities.push_back(l_entity);
}
