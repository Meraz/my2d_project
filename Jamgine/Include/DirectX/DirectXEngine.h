#pragma once

#include <Jamgine/Include/Jamgine.h>
#include <d3d11.h>

using namespace std;
//#include <iostream>

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
			virtual ErrorMessage Initialize(Jamgine::Data_Send p_data);

			virtual void Render(Position p_position, SpriteEffect::SpriteEffect p_spriteEffect);
			virtual void PostRender();

		
		private:
			ID3D11Device*			m_device;
			ID3D11DeviceContext*	m_deviceContext;
			IDXGISwapChain*			m_swapChain;

			HWND					m_handle;
			HINSTANCE				m_hInstance;
			int						m_clientWidth;
			int						m_clientHeight;

		//	ErrorMessage RegisterWindow(HINSTANCE l_hInstance, LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam));
			ErrorMessage RegisterWindow(Jamgine::Data_Send p_data);
			

			ErrorMessage InitializeSwapChain();

		};
	}
}