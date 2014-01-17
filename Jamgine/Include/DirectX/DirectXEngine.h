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
			virtual void Render(Position p_position, SpriteEffect::SpriteEffect p_spriteEffect);
		
		private:
			void InitializeSwapChain();
			void RegisterWindow();


		};
	}
}