#pragma once

#include <Jamgine/Include/Jamgine.h>
#include <Jamgine/Include/Texture/Texture2DManager.h>
#include <Jamgine/Include/DirectX/SpriteData.h>
#include <Jamgine/Include/Shader/ShaderLoader.h>
#include <DirectX/d3d11_1.h>

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
			void InitializeRenderTarget();
			void CreateDepthBuffer();

			virtual void Render(Position p_position, Texture2DInterface* p_textureInterface, SpriteEffect p_spriteEffect);
			virtual void PostRender();

		
		private:
			ID3D11Device*				m_device;
			ID3D11DeviceContext*		m_deviceContext;
			IDXGISwapChain*				m_swapChain;
			ID3D11RenderTargetView*		m_backBuffer_RTV;
			ID3D11UnorderedAccessView*	m_backBuffer_UAV;
			ID3D11Texture2D*			m_depthStencil;
			ID3D11DepthStencilState*	m_depthStencilState;
			ID3D11DepthStencilView*		m_depthStencilView;

			HWND					m_handle;
			HINSTANCE				m_hInstance;
			int						m_clientWidth;
			int						m_clientHeight;

			Texture2DManager*	m_texture2DManager;
			ShaderLoader*		m_shaderLoader;
			ID3D11VertexShader*	m_vertexShader;
			ID3D11PixelShader*	m_pixelShader;
			ID3D11GeometryShader* m_geometryShader;
			ID3D11InputLayout*	m_inputLayout;

			std::vector<SpriteData> m_renderData;

			void LoadShaders();
			void SortSprites();
		//	bool SortAlgorithm(SpriteData p_a, SpriteData p_b);

			ErrorMessage RegisterWindow(Jamgine::Data_Send p_data);
			ErrorMessage InitializeSwapChain();

		};
	}
}