#include <Jamgame.h>

#if defined(WIN32) && !defined(UNIX)
/* Do windows stuff */
#include <Windows.h>
//#include <winerror.h>
//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything.
//--------------------------------------------------------------------------------------
/*
int main()
{
	HINSTANCE hInstance = GetModuleHandle(0);	// http://stackoverflow.com/questions/6728782/how-does-getmodulehandle-work-in-visual-c
	HINSTANCE hPrevInstance = 0;
	LPWSTR lpCmdLine = GetCommandLine();
	//int nCmdShow = GetStartupInfo();
	return 0;
}
*/


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
#include <Windows.h>
#include <TestGame\Include\Jamgame.h>



/*

*/