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
			virtual void Render()
			{

			cout << "Test" << endl;

			}
		};
	}
}