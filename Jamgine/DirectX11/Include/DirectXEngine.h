#pragma once


#include <Jamgine\Include\Jamgine.h>
			using namespace std;
#include <iostream>
namespace Jamgine
{
	namespace DirectX
	{
		class DirectXEngine : public JamgineEngine
		{
		public:
			DirectXEngine();
			~DirectXEngine();
			int a;
			virtual void Render();
		};
	}
}