#include <TestGame/Include/Scene/EditScene.h>

// Definition of forward declaration
#include <TestGame/Include/Entity/RenderEntity.h>
#include <TestGame/Include/Entity/PlayerEntity.h>
#include <TestGame/Include/Entity/EntityFactory.h>

#include <fstream>


EditScene::EditScene(HWND p_handle)
{ 
	m_renderEntity = std::vector<RenderEntity*>();
	m_texture = std::vector<Jamgine::Texture2DInterface*>();
	
	m_handle = p_handle;
	m_creatingBox = false;
	editBox = false;
	m_depthStep = 0.1f;
	m_currTool = CURRENTTOOL::NEWRECT;
	m_changeXAmountSubImage = true;
	m_currentSprite = 0;
	Q = false; W = false; E = false; R = false; T = false; Y = false;
	U = false; I = false; O = false; P = false; S = false; L = false;
	m_totalTextures = 0;
	m_selectedSpriteVibrateTimer = 0;
	m_newSpriteSelected = false;
	m_delete = false;
}

EditScene::~EditScene()
{
}

void EditScene::Initialize(SceneManagerInterface* p_sceneManagerInterface, Jamgine::JamgineEngine* p_engine)
{
	BaseScene::Initialize(p_sceneManagerInterface, p_engine);

	m_camera = Jamgine::Camera(0,0);

	m_texture.resize(3);
	m_engine->LoadTexture(&m_texture[0], "Box1.dds");
	m_engine->LoadTexture(&m_texture[1], "Circle.dds");
	m_engine->LoadTexture(&m_texture[2], "EditScreenButton.dds");
	m_totalTextures = m_texture.size();

}

void EditScene::Update(double p_deltaTime, float p_mousePositionX, float p_mousePositionY, bool p_mouseClicked)
{
	p_mousePositionX += m_camera.position.x;
	p_mousePositionY += m_camera.position.y;

	UpdateCurrentTool();
	tab = GetAsyncKeyState(VK_TAB) & 0x8000;

	if (m_currTool == CURRENTTOOL::NEWRECT)
		NewRect(p_mousePositionX, p_mousePositionY, p_mouseClicked);
	else if (m_currTool == CURRENTTOOL::ENTITY)
		Entity();

	else if (m_currTool == CURRENTTOOL::TEX)
		ChoseTex();
	else if (m_currTool == CURRENTTOOL::ORIGIN)
		SetOrigin(p_mousePositionX, p_mousePositionY, p_mouseClicked);

	else if (m_currTool == CURRENTTOOL::SPRITEEFF)
		SetSpriteEffect();
	else if (m_currTool == CURRENTTOOL::EDITRECT)
		EditRect(p_mousePositionX, p_mousePositionY, p_mouseClicked);
	
	else if (m_currTool == CURRENTTOOL::DEPTH)
		SetDepth(p_mouseClicked);
	else if (m_currTool == CURRENTTOOL::ROTATION)
		SetRotation();
	
	else if (m_currTool == CURRENTTOOL::SUBIMG)
		AmountSubImg(p_mousePositionX, p_mousePositionY, p_mouseClicked);
	else if (m_currTool == CURRENTTOOL::TRANSPARANT)
		SetTransparant();
	else if (m_currTool == CURRENTTOOL::SELECT)
		SelectSprite();
	if (GetAsyncKeyState('S') & 0x8000 && !S)
	{
		SaveCurrentSetup("Level.lvl");
	}
	else if (GetAsyncKeyState('L') & 0x8000 && !L)
	{
		LoadCurrentSetup("Level.lvl");
	}


	if (GetAsyncKeyState(VK_DELETE) & 0x8000 && !m_delete)
	{
		delete m_renderEntity[m_currentSprite];
		m_renderEntity.erase(m_renderEntity.begin() + m_currentSprite);
		m_currentSprite--;
		if (m_currentSprite < 0)
			m_currentSprite = 0;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_camera.position.x -= 0.7;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_camera.position.x += 0.7;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_camera.position.y += 0.7;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_camera.position.y -= 0.7;
	}

	m_prevMouseClick = p_mouseClicked;
	prevtab = tab;
	
	Q = GetAsyncKeyState('Q') & 0x8000;
	W = GetAsyncKeyState('W') & 0x8000;
	E = GetAsyncKeyState('E') & 0x8000;
	R = GetAsyncKeyState('R') & 0x8000;
	T = GetAsyncKeyState('T') & 0x8000;
	Y = GetAsyncKeyState('Y') & 0x8000;
	U = GetAsyncKeyState('U') & 0x8000;
	I = GetAsyncKeyState('I') & 0x8000;
	O = GetAsyncKeyState('O') & 0x8000;
	P = GetAsyncKeyState('P') & 0x8000;
	S = GetAsyncKeyState('S') & 0x8000;
	L = GetAsyncKeyState('L') & 0x8000;
	A = GetAsyncKeyState('A') & 0x8000;
	m_delete = GetAsyncKeyState(VK_DELETE) & 0x8000;


}

void EditScene::NewRect(float p_mousePositionX, float p_mousePositionY, bool p_mouseClicked)
{
	p_mousePositionX = p_mousePositionX / 783 * 800;
	p_mousePositionY = p_mousePositionY / 760 * 800;
		// if a new click has been done and I'm not creating a box	
	if (p_mouseClicked == true && m_prevMouseClick == false && m_creatingBox == false)
	{
		m_creatingBox = true;
		m_firstPos = Position(p_mousePositionX, p_mousePositionY);
	}
	else if (p_mouseClicked == true && m_prevMouseClick == false && m_creatingBox == true)
	{
		m_secondPos = Position(p_mousePositionX, p_mousePositionY);

		float l_width = m_secondPos.x - m_firstPos.x;
		float l_heigth = m_secondPos.y - m_firstPos.y;

		m_renderEntity.push_back(new PlayerEntity());
		m_renderEntity[m_renderEntity.size() - 1]->Initialize(Position(m_firstPos), "EditScreenButton.dds", l_width, l_heigth);

		m_creatingBox = false;
		m_currentSprite = m_renderEntity.size() - 1;
	}
}

void EditScene::Entity()
{
	if (tab && !prevtab)
	{
		if (m_renderEntity[m_currentSprite]->m_entity == ENTITY::RENDER)
			m_renderEntity[m_currentSprite]->m_entity = ENTITY::COLLISION;

		else if (m_renderEntity[m_currentSprite]->m_entity == ENTITY::COLLISION)
			m_renderEntity[m_currentSprite]->m_entity = ENTITY::ANIMATION;

		else if (m_renderEntity[m_currentSprite]->m_entity == ENTITY::ANIMATION)
			m_renderEntity[m_currentSprite]->m_entity = ENTITY::ENENMY;

		else if (m_renderEntity[m_currentSprite]->m_entity == ENTITY::ENENMY)
			m_renderEntity[m_currentSprite]->m_entity = ENTITY::PLAYER;

		else if (m_renderEntity[m_currentSprite]->m_entity == ENTITY::PLAYER)
			m_renderEntity[m_currentSprite]->m_entity = ENTITY::WALL;

		else if (m_renderEntity[m_currentSprite]->m_entity == ENTITY::WALL)
			m_renderEntity[m_currentSprite]->m_entity = ENTITY::RENDER;

		m_renderEntity[m_currentSprite]->m_origin = m_firstPos;
		PrintDebugWithValue("enity:%f \t%f %f \n", (float)m_renderEntity[m_currentSprite]->m_entity, 0, 0);
	}
}

void EditScene::ChoseTex()
{
	if (GetAsyncKeyState(VK_SHIFT) & 0x8000 && tab && !prevtab)
	{
		m_renderEntity[m_currentSprite]->m_textureIndex += -1;
		if (m_renderEntity[m_currentSprite]->m_textureIndex < 0)
			m_renderEntity[m_currentSprite]->m_textureIndex = m_totalTextures - 1;
		m_renderEntity[m_currentSprite]->m_texture = m_texture[m_renderEntity[m_currentSprite]->m_textureIndex];
	}
	else if (tab && !prevtab)
	{
		m_renderEntity[m_currentSprite]->m_textureIndex += 1;
		if (m_renderEntity[m_currentSprite]->m_textureIndex > m_totalTextures - 1)
			m_renderEntity[m_currentSprite]->m_textureIndex = 0;
		m_renderEntity[m_currentSprite]->m_texture = m_texture[m_renderEntity[m_currentSprite]->m_textureIndex];
	}
}

void EditScene::SetOrigin(float p_mousePositionX, float p_mousePositionY, bool p_mouseClicked)
{
	p_mousePositionX = p_mousePositionX / 783 * 800;
	p_mousePositionY = p_mousePositionY / 760 * 800;
	// if a new click has been done and I'm not creating a box	
	if (p_mouseClicked == true && m_prevMouseClick == false)
	{
		m_firstPos = Position(p_mousePositionX, p_mousePositionY);
		m_renderEntity[m_currentSprite]->m_origin = m_firstPos - m_renderEntity[m_currentSprite]->m_position;
		PrintDebugWithValue("origin x:%f y:%f\t %f \n", m_renderEntity[m_currentSprite]->m_origin.x, m_renderEntity[m_currentSprite]->m_origin.y, 0);
	}
	if (tab && !prevtab)
	{
		m_renderEntity[m_currentSprite]->m_origin = Position(0,0);
		PrintDebugWithValue("origin x:%f y:%f\t %f \n", m_renderEntity[m_currentSprite]->m_origin.x, m_renderEntity[m_currentSprite]->m_origin.y, 0);
	}
}

void EditScene::SetSpriteEffect()
{
	if (tab && !prevtab)
	{
		if (m_renderEntity[m_currentSprite]->m_spriteEffect == SpriteEffect::FLIP_NONE)
			m_renderEntity[m_currentSprite]->m_spriteEffect = SpriteEffect::FLIP_HORIZONTALLY;

		else if (m_renderEntity[m_currentSprite]->m_spriteEffect == SpriteEffect::FLIP_HORIZONTALLY)
		m_renderEntity[m_currentSprite]->m_spriteEffect = SpriteEffect::FLIP_VERTICALLY;

		else if (m_renderEntity[m_currentSprite]->m_spriteEffect == SpriteEffect::FLIP_VERTICALLY)
			m_renderEntity[m_currentSprite]->m_spriteEffect = SpriteEffect::FLIP_BOTH;

		else if (m_renderEntity[m_currentSprite]->m_spriteEffect == SpriteEffect::FLIP_BOTH)
			m_renderEntity[m_currentSprite]->m_spriteEffect = SpriteEffect::FLIP_NONE;
		
		m_renderEntity[m_currentSprite]->m_origin = m_firstPos;
		PrintDebugWithValue("SpriteEffect:%f \t%f %f \n", (float)m_renderEntity[m_currentSprite]->m_spriteEffect, 0, 0);
	}
}

void EditScene::EditRect(float p_mousePositionX, float p_mousePositionY, bool p_mouseClicked)
{
	p_mousePositionX = p_mousePositionX / 783 * 800;
	p_mousePositionY = p_mousePositionY / 760 * 800;
	// if a new click has been done and I'm not creating a box	
	if (p_mouseClicked == true && m_prevMouseClick == false && editBox == false)
	{
		editBox = true;
		m_firstPos = Position(p_mousePositionX, p_mousePositionY);
	}
	else if (p_mouseClicked == true && m_prevMouseClick == false && editBox == true)
	{
		m_secondPos = Position(p_mousePositionX, p_mousePositionY);

		float l_width = m_secondPos.x - m_firstPos.x;
		float l_heigth = m_secondPos.y - m_firstPos.y;

		m_renderEntity[m_currentSprite]->Initialize(Position(m_firstPos), "EditScreenButton.dds", l_width, l_heigth);

		editBox = false;
	}
}

void EditScene::SetDepth(bool p_mouseClicked)
{
	// if a new click has been done and I'm not creating a box	
	if (p_mouseClicked == true && m_prevMouseClick == false)
	{
		if (m_depthStep == 0.01f)
			m_depthStep = 0.1f;
		else if (m_depthStep == 0.1f)
			m_depthStep = 0.01f;
		PrintDebugWithValue("m_depthStep x:%f y:%f\t %f \n", m_depthStep, 0, 0);
	}
	if (GetAsyncKeyState(VK_SHIFT) & 0x8000 && tab && !prevtab)
	{
		m_renderEntity[m_currentSprite]->m_depth -= m_depthStep;
		if (m_renderEntity[m_currentSprite]->m_depth < 0)
			m_renderEntity[m_currentSprite]->m_depth = 1.0f;
		PrintDebugWithValue("depth x:%f y:%f\t %f \n", m_renderEntity[m_currentSprite]->m_depth, 0, 0);
	}
	else if (tab && !prevtab)
	{
		m_renderEntity[m_currentSprite]->m_depth += m_depthStep;
		if (m_renderEntity[m_currentSprite]->m_depth > 1.0f)
			m_renderEntity[m_currentSprite]->m_depth = 0;
		PrintDebugWithValue("depth x:%f y:%f\t %f \n", m_renderEntity[m_currentSprite]->m_depth, 0, 0);
	}
}

void EditScene::SetRotation()
{
	if (tab && !prevtab)
	{
		m_renderEntity[m_currentSprite]->m_rotation += 2 * 3.1415 / 16.0;
		if (m_renderEntity[m_currentSprite]->m_rotation > 2 * 3.1415)
			m_renderEntity[m_currentSprite]->m_rotation = 0;

		PrintDebugWithValue("rotation:%f \t%f %f \n", (float)m_renderEntity[m_currentSprite]->m_rotation, 0, 0);
	}
}

void EditScene::AmountSubImg(float p_mousePositionX, float p_mousePositionY, bool p_mouseClicked)
{

	if (p_mouseClicked == true && m_prevMouseClick == false)
	{
		m_changeXAmountSubImage = !m_changeXAmountSubImage;

		if (m_changeXAmountSubImage == true)
			PrintDebugWithValue("m_changeXAmountSubImage: true\t\t %f %f %f\n", 0, 0, 0);
		else
			PrintDebugWithValue("m_changeXAmountSubImage: false\t\t %f %f %f\n", 0, 0, 0);
	}
	if (tab && !prevtab)
	{
		if (m_changeXAmountSubImage)
		{
			m_renderEntity[m_currentSprite]->m_currentSubImage.x += 1;
			if (m_renderEntity[m_currentSprite]->m_currentSubImage.x > MAX_SUB_IMAGES)
				m_renderEntity[m_currentSprite]->m_currentSubImage.x = 0;
		}
		else
		{	m_renderEntity[m_currentSprite]->m_currentSubImage.y += 1;
			if (m_renderEntity[m_currentSprite]->m_currentSubImage.y > MAX_SUB_IMAGES)
				m_renderEntity[m_currentSprite]->m_currentSubImage.y = 0;
		}
		PrintDebugWithValue("m_currentSubImage: %f %f \t%f\n", m_renderEntity[m_currentSprite]->m_currentSubImage.x, m_renderEntity[m_currentSprite]->m_currentSubImage.y, 0);
	}
}

void EditScene::SetTransparant()
{
	if (tab && !prevtab)
	{
		m_renderEntity[m_currentSprite]->m_hasTransparent = !m_renderEntity[m_currentSprite]->m_hasTransparent;

		if (m_renderEntity[m_currentSprite]->m_hasTransparent == true)
			PrintDebugWithValue("transparent: true\t\t %f %f %f\n", 0, 0, 0);
		else
			PrintDebugWithValue("transparent: false\t\t %f %f %f\n", 0, 0, 0);
	}
}

void EditScene::SelectSprite()
{
	if (GetAsyncKeyState(VK_SHIFT) & 0x8000 && tab && !prevtab)
	{
		m_currentSprite--;		
		if (m_currentSprite < 0)
			m_currentSprite = m_renderEntity.size() - 1;
		m_originalSpritePosition = m_renderEntity[m_currentSprite]->m_position;
		m_newSpriteSelected = true;
		m_selectedSpriteVibrateTimer = 0;
	}
	else if (tab && !prevtab)
	{
		m_currentSprite++;
		if (m_currentSprite > m_renderEntity.size() - 1)
			m_currentSprite = 0;
		m_originalSpritePosition = m_renderEntity[m_currentSprite]->m_position;
		m_newSpriteSelected = true;
		m_selectedSpriteVibrateTimer = 0;
	}
}

void EditScene::UpdateCurrentTool()
{
	if (GetAsyncKeyState('Q') & 0x8000 && !Q)
	{
		m_currTool = CURRENTTOOL::NEWRECT;
		PrintDebug("newrect\n");
	}
	else if (GetAsyncKeyState('W') & 0x8000 && !W)
	{
		m_currTool = CURRENTTOOL::ENTITY;
		PrintDebug("entity\n");
	}
	else if (GetAsyncKeyState('E') & 0x8000 && !E)
	{
		m_currTool = CURRENTTOOL::TEX;
		PrintDebug("chosetex\n");
	}
	else if (GetAsyncKeyState('R') & 0x8000 && !R)
	{
		m_currTool = CURRENTTOOL::ORIGIN;
		PrintDebug("setorigin\n");
	}
	else if (GetAsyncKeyState('T') & 0x8000 && !T)
	{
		m_currTool = CURRENTTOOL::SPRITEEFF;
		PrintDebug("Setspriteeffect\n");
	}
	else if (GetAsyncKeyState('Y') & 0x8000 && !Y)
	{
		m_currTool = CURRENTTOOL::EDITRECT;
		PrintDebug("editrect\n");
	}
	else if (GetAsyncKeyState('U') & 0x8000 && !U)
	{
		m_currTool = CURRENTTOOL::DEPTH;
		PrintDebug("setdepth\n");
	}
	else if (GetAsyncKeyState('I') & 0x8000 && !I)
	{
		m_currTool = CURRENTTOOL::ROTATION;
		PrintDebug("setrotation\n");
	}
	else if (GetAsyncKeyState('O') & 0x8000 && !O)
	{
		m_currTool = CURRENTTOOL::SUBIMG;
		PrintDebug("amountsubimg\n");
	}
	else if (GetAsyncKeyState('P') & 0x8000 && !P)
	{
		m_currTool = CURRENTTOOL::TRANSPARANT;
		PrintDebug("Settransparant\n");
	}
	else if (GetAsyncKeyState('A') & 0x8000 && !A)
	{
		m_currTool = CURRENTTOOL::SELECT;
		PrintDebug("Select new sprite\n");
	}
}

void EditScene::Render()
{
	int a = m_renderEntity.size();
	if (a > 0)
	{
		for (int i = 0; i < a ; i++)
		{
			m_renderEntity[i]->Render(m_engine);
		}
	}

	if (m_newSpriteSelected)
	{
		if (m_selectedSpriteVibrateTimer++ < 1000)
		{
			if (m_selectedSpriteVibrateTimer % 2 == 0)
				m_renderEntity[m_currentSprite]->m_position -= Position(3, 3);
			else
				m_renderEntity[m_currentSprite]->m_position += Position(3, 3);
		}
		else
		{
			m_newSpriteSelected = false;
			m_renderEntity[m_currentSprite]->m_position = m_originalSpritePosition;
		}
	}

	m_engine->PostRender(&m_camera);
}

void EditScene::SaveCurrentSetup(char* p_fileName)
{
	using namespace std;

	ofstream l_file;
	l_file.open(p_fileName);

	unsigned int l_totalObjects = m_renderEntity.size();
	for (unsigned int i = 0; i < l_totalObjects; i++)
	{
		l_file << m_renderEntity[i]->ToFile().str();
		l_file << "\n";
	}
	l_file.close();
}

void EditScene::LoadCurrentSetup(char* p_fileName)
{
	using namespace std;

	EntityFactory* m_entityFactory;
	m_entityFactory = new EntityFactory();

	ifstream l_stream;
	l_stream.open(p_fileName);

	unsigned int l_totalObjects = m_renderEntity.size();
	

	char l_buffer[1024];

	//float 

	while (l_stream.getline(l_buffer, 1024))
	{
		char lKey[8];

		// Texture
		RenderEntity* l_renderEntity;
		sscanf_s(l_buffer, "%i ", lKey, sizeof(lKey));
		l_renderEntity = m_entityFactory->CreateObject(lKey[0], l_buffer);
		m_renderEntity.push_back(l_renderEntity);
	}

	l_stream.close();
	delete m_entityFactory;
}

void EditScene::PrintDebug(char* p_message)
{
	char a[256];
	sprintf(a, p_message);
	OutputDebugStringA(a);
}

void EditScene::PrintDebugWithValue(char* p_message, float p_value1, float p_value2, float p_value3)
{
	char a[256];
	sprintf(a, p_message, p_value1, p_value2, p_value3);
	OutputDebugStringA(a);
}