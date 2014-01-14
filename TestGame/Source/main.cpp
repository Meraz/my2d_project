#include <Jamgine\Include\Jamgine.h>

#include <Windows.h>

int main()
{
	Jamgine::JamgineEngine* a = nullptr;
	//Jamgine::ReleaseEngine();
	Jamgine::CreateEngine(a, Jamgine::GraphicalSystem::DIRECTX);
	system("pause");

	return 0;
}