#include <TestGame/Include/Scene/EditScene.h>

// Definition of forward declaration
#include <TestGame/Include/Entity/RenderEntity.h>
#include <TestGame/Include/Entity/PlayerEntity.h>
#include <TestGame/Include/Entity/EntityFactory.h>

#include <fstream>



EditScene::EditScene()
{ 
	m_renderEntity = std::vector<RenderEntity*>();
	m_editSpecific = std::vector<RenderEntity*>();
	
	m_creatingBox = false;
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

	
//	SaveCurrentSetup("TESTFILE.txt");
//	SaveCurrentSetup("TESTFILE.txt");
//	LoadCurrentSetup("TESTFILE.txt");
}

void EditScene::Update(double p_deltaTime, int p_mousePositionX, int p_mousePositionY, bool p_mouseClicked)
{
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
		float l_heigth = m_firstPos.y - m_secondPos.y;

		m_renderEntity.push_back(new PlayerEntity());
		m_renderEntity[m_renderEntity.size() - 1]->Initialize(Position(m_firstPos), "EditScreenButton.dds", l_width, l_heigth);
		m_creatingBox = false;
	}

	m_prevMouseClick = p_mouseClicked;
}

void EditScene::Render()
{
	for (int i = 0; i < 30; i++)
	{
		m_editSpecific[i]->Render(m_engine);
	}
	int a = m_renderEntity.size();
	if (a > 0)
	{
		for (int i = 0; i < m_renderEntity.size() - 1; i++)
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