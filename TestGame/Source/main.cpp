#include <TestGame/Include/Jamgame.h>
#if defined(WIN32) && !defined(UNIX)
/* Do windows stuff */
#include <Windows.h>
#include <SubsystemTest/Include/Math1.h>
#include <DynamicLoader/Include/DynamicLoader.h>


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	void* m_math1Module = nullptr;
	m_math1Module = DynamicLoader::LoadSharedLibrary("SubsystemTest.dll");

	//if (m_math1Module != nullptr)
	
		CREATEMATHINTERFACE libMath1Lib = (CREATEMATHINTERFACE)DynamicLoader::LoadProcess(m_math1Module, "CreateMathInterface");
		Jamgine::MathSpace::Math1* math1 = (Jamgine::MathSpace::Math1*)libMath1Lib();
		float test = math1->floatAdd(5.0f, 7.0f);

	


	Jamgame* l_jamgame = new Jamgame();
	l_jamgame->Initialize(hInstance, lpCmdLine, nCmdShow);
	l_jamgame->Run();

	delete l_jamgame;
	return 0;
}

#elif defined(UNIX) && !defined(WIN32)
/* Do linux stuff */
int main()
{
Jamgine::JamgineEngine* a = nullptr;
Jamgine::JamgineEngine::CreateEngine(&a, Jamgine::GraphicalSystem::DIRECTX);
//	Jamgine::JamgineEngine::ReleaseEngine();

//a->Render();
system("pause");


return 0;
}

#else
/* Error, both can't be defined or undefined same time */

#endif