#pragma once

#include <Jamgine/Include/Jamgine.h>
#include <Jamgine/Include/Texture/Texture2DManager.h>
#include <d3d11.h>

#include <vector>


namespace Jamgine
{
	namespace DirectX
	{
		struct SpriteData;

		class DirectXEngine : public JamgineEngine
		{
		public:
			DirectXEngine();
			~DirectXEngine();
			
			
			virtual ErrorMessage Initialize(void* p_data);			
			virtual ErrorMessage Initialize(Jamgine::Data_Send p_data);
			virtual ErrorMessage LoadTexture(Texture2DInterface** p_texture2DInterface, char* p_filePath);

			virtual void Render(Position p_position, Texture2DInterface* p_textureInterface, SpriteEffect p_spriteEffect);
			virtual void PostRender();

		
		private:
			ID3D11Device*			m_device;
			ID3D11DeviceContext*	m_deviceContext;
			IDXGISwapChain*			m_swapChain;

			HWND					m_handle;
			HINSTANCE				m_hInstance;
			int						m_clientWidth;
			int						m_clientHeight;

			Texture2DManager* m_texture2DManager;

			std::vector<SpriteData> m_renderData;

			void SortSprites();

			ErrorMessage RegisterWindow(Jamgine::Data_Send p_data);
			ErrorMessage InitializeSwapChain();

		};
	}
}