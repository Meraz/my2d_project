#include <TestGame/Include/Jamgame.h>

#if defined(WIN32) && !defined(UNIX)
/* Do windows stuff */
#include <Windows.h>


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
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