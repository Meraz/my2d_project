#pragma once

#include <Jamgine\Include\Jamgine.h>
#include <DirectX\D3DX11.h>

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
			virtual ErrorMessage Initialize(void* p_data);

			virtual void Render(Position p_position, SpriteEffect::SpriteEffect p_spriteEffect);
		
		private:
			ID3D11Device*			m_device;
			ID3D11DeviceContext*	m_context;
			HINSTANCE				m_hInstance;
			HWND					m_handle;
			int						m_clientWidth;
			int						m_clientHeight;


			void InitializeSwapChain();
			void RegisterWindow(HINSTANCE l_hInstance, LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam));

		};
	}
}