#if defined(WIN32) && !defined(UNIX)
/* Do windows stuff */
#include <Windows.h>
//#include <winerror.h>

#elif defined(UNIX) && !defined(WIN32)
/* Do linux stuff */


#else
/* Error, both can't be defined or undefined same time */

#endif
#include <Windows.h>
#include <TestGame\Include\Jamgame.h>


//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	Jamgame* l_jamgame = new Jamgame();
	l_jamgame->Initialize(hInstance, lpCmdLine, nCmdShow);
	l_jamgame->Run();

	delete l_jamgame;
	return 0;
}

/*
int main()
{
Jamgine::JamgineEngine* a = nullptr;
Jamgine::JamgineEngine::CreateEngine(&a, Jamgine::GraphicalSystem::DIRECTX);
//	Jamgine::JamgineEngine::ReleaseEngine();

//a->Render();
system("pause");


return 0;
}
*/