#include <Jamgine\Include\Jamgine.h>

#include <Windows.h>

int main()
{
	Jamgine::JamgineEngine* a = nullptr;
//	Jamgine::JamgineEngine::CreateEngine(&a, Jamgine::GraphicalSystem::DIRECTX);
//	Jamgine::JamgineEngine::ReleaseEngine();

	a->Render();
	system("pause");
	

	return 0;
}