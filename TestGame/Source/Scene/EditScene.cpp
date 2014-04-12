#include <TestGame/Include/Scene/EditScene.h>

// Definition of forward declaration
#include <TestGame/Include/Entity/RenderEntity.h>
#include <TestGame/Include/Entity/PlayerEntity.h>
#include <TestGame/Include/Entity/EntityFactory.h>

#include <fstream>


EditScene::EditScene(HWND p_handle)
{ 
	m_renderEntity = std::vector<RenderEntity*>();
	m_editSpecific = std::vector<RenderEntity*>();
	m_texture = std::vector<Jamgine::Texture2DInterface*>();
	
	m_handle = p_handle;
	m_creatingBox = false;
	m_currTool = CURRENTTOOL::NEWRECT;
	m_currentSprite = 0;
	Q = false; W = false; E = false; R = false; T = false; Y = false;
	U = false; I = false; O = false; P = false; S = false; L = false;

}

EditScene::~EditScene()
{
}

void EditScene::Initialize(SceneManagerInterface* p_sceneManagerInterface, Jamgine::JamgineEngine* p_engine)
{
	BaseScene::Initialize(p_sceneManagerInterface, p_engine);

	m_camera = Jamgine::Camera(0,0);

	for (int i = 0; i < 30; i++)
	{
		m_editSpecific.push_back(new PlayerEntity());
		m_editSpecific[i]->Initialize(Position(i * 50 + 2, 50), "EditScreenButton.dds", 45, 45);
	}
	m_editSpecific.push_back(new PlayerEntity());
	m_editSpecific[30]->Initialize(Position(750, 750), "EditScreenButton.dds", 50, 50);

	m_texture.resize(30);
	m_engine->LoadTexture(&m_texture[0], "Box1.dds");
	m_engine->LoadTexture(&m_texture[1], "Box2.dds");
	
//	SaveCurrentSetup("TESTFILE.txt");
//	SaveCurrentSetup("TESTFILE.txt");
//	LoadCurrentSetup("TESTFILE.txt");

}

void EditScene::Update(double p_deltaTime, float p_mousePositionX, float p_mousePositionY, bool p_mouseClicked)
{
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
		EditRect();
	
	else if (m_currTool == CURRENTTOOL::DEPTH)
		SetDepth();
	else if (m_currTool == CURRENTTOOL::ROTATION)
		SetRotation();
	
	else if (m_currTool == CURRENTTOOL::SUBIMG)
		AmountSubImg();
	else if (m_currTool == CURRENTTOOL::TRANSPARANT)
		Entity();
	if (GetAsyncKeyState('S') & 0x8000 && !S)
	{
		SaveCurrentSetup("Level.lvl");
	}
	else if (GetAsyncKeyState('L') & 0x8000 && !L)
	{
		SaveCurrentSetup("Level.lvl");
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
}

void EditScene::ChoseTex()
{

}

void EditScene::SetOrigin(float p_mousePositionX, float p_mousePositionY, bool p_mouseClicked)
{
	p_mousePositionX = p_mousePositionX / 783 * 800;
	p_mousePositionY = p_mousePositionY / 760 * 800;
	// if a new click has been done and I'm not creating a box	
	if (p_mouseClicked == true && m_prevMouseClick == false)
	{
		m_firstPos = Position(p_mousePositionX, p_mousePositionY);
		m_renderEntity[m_currentSprite]->m_origin = m_firstPos;
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

void EditScene::EditRect()
{
}

void EditScene::SetDepth()
{
}
void EditScene::SetRotation()
{
}
void EditScene::AmountSubImg()
{
}
void EditScene::SetTransparant()
{

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
}


void EditScene::Render()
{
	for (int i = 0; i < 31; i++)
	{
		m_editSpecific[i]->Render(m_engine);
	}
	int a = m_renderEntity.size();
	if (a > 0)
	{
		for (int i = 0; i < a ; i++)
		{
			m_renderEntity[i]->Render(m_engine);
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