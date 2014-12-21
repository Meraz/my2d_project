#pragma once

// Official libs
#include <vector>

// Official in-project includes 
//#include <Jamgine/Include/DirectX/JDirectXShared.h>
#include <DirectXMath.h>	// DOsen't work to include via DirectX/DirectXMath. No idea why, I think I might have done something wrong with cMake

// Project files
#include <Jamgine/Include/Jamgine.h>
#include <Jamgine/Include/DirectX/JDirectXTexture2DManager.h>
#include <Jamgine/Include/Shader/ShaderLoader.h>
#include <Jamgine/Include/MemoryAllocator/SingleFrameStack.h>

namespace Jamgine
{
	namespace JDirectX
	{
		struct SpriteData;
		struct CameraMatrix
		{
			DirectX::XMFLOAT4X4 m_view;
			DirectX::XMFLOAT4X4 m_proj;
		};

		class DirectXEngine : public JamgineEngine
		{
		public:
			DirectXEngine();
			virtual ~DirectXEngine();
			
			virtual ErrorMessage Initialize(void* p_data) override;
			virtual ErrorMessage Initialize(Jamgine::Data_Send p_data) override;
			virtual ErrorMessage LoadTexture(Texture2D** p_texture2DInterface, char* p_filePath) override;
			
			virtual	void Render(Rectangle p_rectangle, Texture2D* p_texture) override;
			virtual	void Render(Rectangle p_rectangle, Texture2D* p_texture, float p_depth) override;
			virtual	void Render(JFloat2 p_position, float p_width, float p_height, Texture2D* p_texture) override;
			virtual	void Render(JFloat2 p_position, float p_width, float p_height, Texture2D* p_texture, float p_depth) override;

			// Render with a pre-filled SpriteData struct
			virtual void Render(Jamgine::SpriteData p_spriteData) override;

			virtual void PostRender() override;
					
		private:
			///////////
			// Variables

			// Windows and window specific
			HWND		m_handle;
			HINSTANCE	m_hInstance;
			int			m_clientWidth;
			int			m_clientHeight;

			std::vector<Jamgine::SpriteData> m_renderData;
			DirectX::XMFLOAT4X4 m_view;


			///////////
			// Pointers
			
			// DirectX pointers
			ID3D11Device*				m_device;
			ID3D11DeviceContext*		m_deviceContext;
			IDXGISwapChain*				m_swapChain;
			ID3D11RenderTargetView*		m_backBuffer_RTV;
			ID3D11UnorderedAccessView*	m_backBuffer_UAV;
			ID3D11Texture2D*			m_depthStencil;
			ID3D11DepthStencilState*	m_depthStencilState;
			ID3D11DepthStencilView*		m_depthStencilView;
			ID3D11Buffer*				m_perTextureBuffer;		// not sure
			ID3D11Buffer*				m_vertexBuffer;			// Vertex data
			ID3D11Buffer*				m_matrices;				// view and proj for gshader
			ID3D11SamplerState*			m_samplerState;
			ID3D11RasterizerState*		m_rasterizerState;
			ID3D11BlendState*			m_blendState;

			// User defined pointers
			JDirectXTexture2DManager*	m_texture2DManager;
			ShaderLoader*		m_shaderLoader;
			ID3D11VertexShader*	m_vertexShader;
			ID3D11PixelShader*	m_pixelShader;
			ID3D11GeometryShader* m_geometryShader;
			ID3D11InputLayout*	m_inputLayout;


			///////////
			// Functions

			// Initialize functions
			HRESULT RegisterWindow(Jamgine::Data_Send p_data);
			HRESULT InitializeSwapChain();
			void	SetViewport();
			HRESULT CreateDepthBuffer();
			HRESULT InitializeRenderTarget();
			
			HRESULT CreateRasterizers();			
			HRESULT SetBlendState();		

			HRESULT CreateBuffer();
			HRESULT LoadShaders();
			HRESULT AllocateMemory();

			// Other functions
			void SortSprites();

			// Camera functions
			void updateCameraMatrix();

			// Test Camera
			JCamera* m_camera;
			CameraMatrix m_cameraMatrix;

			// Memory stuff
			SingleFrameStack* m_singleFrameStack;
		};
	}
}