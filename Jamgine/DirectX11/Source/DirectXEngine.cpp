#include <Jamgine\DirectX11\Include\DirectXEngine.h>

namespace Jamgine
{
	namespace DirectX
	{
		
		DirectXEngine::DirectXEngine()
		{
			a = 5;
		}

		DirectXEngine::~DirectXEngine()
		{

		}

		void DirectXEngine::Render()
		{
			cout << "Test" << endl;
		}
	}
}