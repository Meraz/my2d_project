#pragma once

#include <Jamgine/Include/Jamgine.h>
#include <Jamgine/Include/Texture/Texture2DManager.h>
#include <Jamgine/Include/DirectX/SpriteData.h>
#include <Jamgine/Include/Shader/ShaderLoader.h>
#include <DirectX/d3d11_1.h>
#include <DirectX/DirectXMath.h>

#include <vector>


namespace Jamgine
{
	namespace JDirectX
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

			virtual void Render(Position p_position,
				Position p_origin,
				Position p_textureOffset,
				Texture2DInterface* p_texture,
				SpriteEffect p_spriteEffect,
				float p_width,
				float p_height,
				float p_depth,
				float p_rotation,
				bool p_hasTransparent);

			virtual void Render(
				Position p_position,
				Position p_origin,
				Position p_textureOffset,
				Texture2DInterface* p_texture,
				float p_width,
				float p_height,
				float p_depth,
				float p_rotation);
			virtual void Render(Position p_position,
				Position p_textureOffset,
				Texture2DInterface* p_texture,
				float p_width,
				float p_height,
				float p_depth);
			virtual void Render(Position p_position, Position p_textureOffset,
				Texture2DInterface* p_texture,
				SpriteEffect p_spriteEffect,
				float p_width,
				float p_height,
				float p_depth
				);

		/*
						Position p_position,
				Position p_origin,
				Position p_textureOffset,
				Texture2D* p_texture,
				SpriteEffect p_spriteEffect,
				float p_width,
				float p_height,
				float p_depth,
				float p_rotation
		*/


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
			ID3D11Buffer*				m_perFrameBuffer;
			ID3D11Buffer*				m_perTextureBuffer;
			ID3D11Buffer*				m_perWindowChangeBuffer;
			ID3D11Buffer*				m_vertexBuffer;
			ID3D11SamplerState*			m_samplerState;
			ID3D11RasterizerState*		m_rasterizerState;
			ID3D11BlendState*			m_blendState;

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

			DirectX::XMFLOAT4X4 m_view;

			void LoadShaders();
			void SortSprites();
			void CreateBuffer();
			HRESULT CreateRasterizers();
			void SetViewport();
			void SetBlendState();

			ErrorMessage RegisterWindow(Jamgine::Data_Send p_data);
			ErrorMessage InitializeSwapChain();

		};
	}
}