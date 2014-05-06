// Official libs
#include <exception>
#include <algorithm>  

#include <DirectXColors.h>

// Project files
#include <Jamgine/Include/DirectX/DirectXEngine.h>
#include <Jamgine/Include/DirectX/DirectXShared.h>

namespace Jamgine
{
	namespace JDirectX
	{		
		struct Vertex
		{
			DirectX::XMFLOAT3 position;
			DirectX::XMFLOAT2 origin;
			DirectX::XMFLOAT2 offset;
			DirectX::XMFLOAT2 texture_offset;
			float  rotation;
			DirectX::XMFLOAT2 TextureDeltaUVSize;	// 1 / number of subpictures
			unsigned int flip;
			
			Vertex()
			{
			
			}

			Vertex(SpriteData input)
			{
				position = DirectX::XMFLOAT3(input.position.x, input.position.y, input.depth);
				origin	 = DirectX::XMFLOAT2(input.origin.x, input.origin.y);
				offset	 = DirectX::XMFLOAT2(input.width, input.height);
				texture_offset = DirectX::XMFLOAT2(input.textureOffset.x, input.textureOffset.y);
				rotation = input.rotation;
				TextureDeltaUVSize = DirectX::XMFLOAT2(1/input.textureDelta.x, 1/input.textureDelta.y);
				flip = (unsigned int)input.spriteEffect;
			}
		};

		DirectXEngine::DirectXEngine()
			: m_device(nullptr), m_deviceContext(nullptr), m_swapChain(nullptr), 
			  m_backBuffer_RTV(nullptr), m_backBuffer_UAV(nullptr), m_depthStencil(nullptr), m_depthStencilState(nullptr),
			  m_depthStencilView(nullptr), m_perFrameBuffer(nullptr), m_perTextureBuffer(nullptr), m_perWindowChangeBuffer(nullptr),
			  m_vertexBuffer(nullptr), m_samplerState(nullptr), m_rasterizerState(nullptr), m_blendState(nullptr),
			  m_texture2DManager(nullptr), 	m_shaderLoader(nullptr), m_vertexShader(nullptr), m_pixelShader(nullptr), m_geometryShader(nullptr),
			  m_inputLayout(nullptr)
		{
			DirectX::XMStoreFloat4x4(&m_view, DirectX::XMMatrixIdentity());
		}

		DirectXEngine::~DirectXEngine()
		{

		}

		ErrorMessage DirectXEngine::Initialize(void* p_data)
		{
			ErrorMessage l_errorMessage = J_OK;
			Jamgine::Data_Send l_data;
			try
			{
				l_data = *(Jamgine::Data_Send*)p_data;
			}
			catch (std::exception e)
			{
				return J_FAIL;
			}
			
			// Run regular init
			l_errorMessage = Initialize(l_data);
			if(l_errorMessage != J_OK)
				return J_FAIL;

			return l_errorMessage;
		}

		ErrorMessage DirectXEngine::Initialize(Jamgine::Data_Send p_data)
		{
			ErrorMessage l_errorMessage = J_OK;

			m_hInstance		= p_data.hInstance;
			m_clientWidth	= p_data.clientWidth;
			m_clientHeight	= p_data.clientHeight;
			
			// Register window
			l_errorMessage  = RegisterWindow(p_data);
				if(l_errorMessage != J_OK)
				return J_FAIL; 

			// Init swapchain and device
			l_errorMessage = InitializeSwapChain();
			if(l_errorMessage != J_OK)
				return J_FAIL; 

			// Create texturemanger
			l_errorMessage = Texture2DManager::CreateTexture2DManager(&m_texture2DManager);
			m_texture2DManager->Initialize(m_device);
			if(l_errorMessage != J_OK)
				return J_FAIL; 

			SetViewport();
			CreateDepthBuffer();
			InitializeRenderTarget();
			
			CreateRasterizers();			
			SetBlendState();		

			CreateBuffer();
			LoadShaders();

			return l_errorMessage;
		}

		HRESULT DirectXEngine::RegisterWindow(Jamgine::Data_Send p_data)
		{
			HRESULT l_hr = S_OK;

			WNDCLASS l_wndClass;
			l_wndClass.style         = CS_HREDRAW | CS_VREDRAW;
			l_wndClass.lpfnWndProc   = p_data.messageProc; 
			l_wndClass.cbClsExtra    = 0;
			l_wndClass.cbWndExtra    = 0;
			l_wndClass.hInstance     = m_hInstance;
			l_wndClass.hIcon         = LoadIcon(0, IDI_APPLICATION);
			l_wndClass.hCursor       = LoadCursor(0, IDC_ARROW);
			l_wndClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
			l_wndClass.lpszMenuName  = 0;
			l_wndClass.lpszClassName = L"Testgame";
			
			if (!RegisterClass(&l_wndClass))
			{
				return S_FALSE;
			}
							
			// Create window
			RECT rc = { 0, 0, m_clientHeight, m_clientWidth};

			m_handle = CreateWindow(
				L"TestGame",
				L"Welcome to this window",
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, CW_USEDEFAULT,
				rc.right - rc.left,
				rc.bottom - rc.top,
				NULL,
				NULL, 
				p_data.hInstance, 
				NULL);

			if(!m_handle)
			{
				return S_FALSE;
			}

			ShowWindow( m_handle, SW_SHOW);

			return l_hr;
		}	

		HRESULT DirectXEngine::InitializeSwapChain()
		{
			HRESULT l_hr = S_OK;

			DXGI_SWAP_CHAIN_DESC l_swapChainDesc;
			ZeroMemory( &l_swapChainDesc, sizeof( l_swapChainDesc ) );

			l_swapChainDesc.BufferDesc.Width					= m_clientWidth;
			l_swapChainDesc.BufferDesc.Height					= m_clientHeight;
			l_swapChainDesc.BufferDesc.RefreshRate.Numerator	= 60;			
			l_swapChainDesc.BufferDesc.RefreshRate.Denominator	= 1;			
			l_swapChainDesc.BufferDesc.Format					= DXGI_FORMAT_R8G8B8A8_UNORM;
			l_swapChainDesc.SampleDesc.Count					= 1;
			l_swapChainDesc.SampleDesc.Quality					= 0;
			l_swapChainDesc.BufferUsage							= DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_UNORDERED_ACCESS;
			l_swapChainDesc.BufferCount							= 1;
			l_swapChainDesc.OutputWindow						= m_handle;
			l_swapChainDesc.Windowed							= true;

			D3D_FEATURE_LEVEL featureLevelsToTry[] = {
				D3D_FEATURE_LEVEL_11_0,
				D3D_FEATURE_LEVEL_10_1,
				D3D_FEATURE_LEVEL_10_0
			};

			UINT createDeviceFlags = 0;
			#ifdef _DEBUG
				createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
			#endif
				D3D_FEATURE_LEVEL l_initiatedFeatureLevel;

			l_hr = D3D11CreateDeviceAndSwapChain(
				NULL,
				D3D_DRIVER_TYPE_HARDWARE,
				NULL,
				createDeviceFlags,
				featureLevelsToTry,
				ARRAYSIZE(featureLevelsToTry),
				D3D11_SDK_VERSION,
				&l_swapChainDesc,
				&m_swapChain,
				&m_device,
				&l_initiatedFeatureLevel,
				&m_deviceContext);

			return l_hr;
		}
		
		void DirectXEngine::SetViewport()
		{
			D3D11_VIEWPORT vp;
			vp.Width		= (FLOAT)m_clientWidth;
			vp.Height		= (FLOAT)m_clientHeight;
			vp.MinDepth		= 0.0f;
			vp.MaxDepth		= 1.0f;
			vp.TopLeftX		= 0;
			vp.TopLeftY		= 0;
			m_deviceContext->RSSetViewports(1, &vp);
		}

		HRESULT DirectXEngine::CreateDepthBuffer()
		{
			HRESULT l_hr = S_OK;

			// Create depth stencil texture
			D3D11_TEXTURE2D_DESC descDepth;
			ZeroMemory(&descDepth, sizeof(descDepth));
			descDepth.Width				= m_clientWidth;
			descDepth.Height			= m_clientHeight;
			descDepth.MipLevels			= 1;
			descDepth.ArraySize			= 1;
			descDepth.Format			= DXGI_FORMAT_D24_UNORM_S8_UINT;
			descDepth.SampleDesc.Count	= 1;
			descDepth.SampleDesc.Quality = 0;
			descDepth.Usage				= D3D11_USAGE_DEFAULT;
			descDepth.BindFlags			= D3D11_BIND_DEPTH_STENCIL;
			descDepth.CPUAccessFlags	= 0;
			descDepth.MiscFlags			= 0;

			l_hr = m_device->CreateTexture2D(&descDepth, nullptr, &m_depthStencil);
			if(FAILED(l_hr))
				return l_hr;

			D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
			ZeroMemory(&descDSV, sizeof(descDSV));
			descDSV.Format				= descDepth.Format;
			descDSV.ViewDimension		= D3D11_DSV_DIMENSION_TEXTURE2D;
			descDSV.Texture2D.MipSlice	= 0;
			l_hr = m_device->CreateDepthStencilView(m_depthStencil, &descDSV, &m_depthStencilView);
			if(FAILED(l_hr))
				return l_hr;

			//create states
			D3D11_DEPTH_STENCIL_DESC dsDesc;

			// Depth test parameters
			dsDesc.DepthEnable = true;
		//	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
			dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

			// Stencil test parameters
			dsDesc.StencilEnable = true;	// YES?1
			dsDesc.StencilReadMask = 0xFF;
			dsDesc.StencilWriteMask = 0xFF;
			// Stencil operations if pixel is front-facing
			dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
			dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

			// Stencil operations if pixel is back-facing
			dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
			dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

			l_hr = m_device->CreateDepthStencilState(&dsDesc, &m_depthStencilState);

			if(FAILED(l_hr))
				return l_hr;

			return l_hr;
		}

		HRESULT DirectXEngine::InitializeRenderTarget()
		{
			HRESULT l_hr = S_OK;
			ID3D11Texture2D* l_backBuffer;
			l_hr = m_swapChain	->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&l_backBuffer);
			l_hr = m_device		->CreateRenderTargetView	(l_backBuffer, nullptr, &m_backBuffer_RTV);
			l_hr = m_device		->CreateUnorderedAccessView	(l_backBuffer, nullptr, &m_backBuffer_UAV);

			if(FAILED(l_hr))
			{
				l_backBuffer->Release();
				return l_hr;
			}
			m_deviceContext->OMSetRenderTargets(1, &m_backBuffer_RTV, m_depthStencilView);
			l_backBuffer->Release();

			return l_hr;
		}

		HRESULT DirectXEngine::CreateRasterizers()
		{
			HRESULT l_hr = S_OK;
			D3D11_RASTERIZER_DESC desc;

			desc.FillMode = D3D11_FILL_SOLID;
			desc.CullMode = D3D11_CULL_NONE;
			desc.FrontCounterClockwise = false;
			desc.DepthBias = 0;
			desc.SlopeScaledDepthBias = 0.0f;
			desc.DepthBiasClamp = 0.0f;
			desc.DepthClipEnable = true;
			desc.ScissorEnable = false;
			desc.MultisampleEnable = false;
			desc.AntialiasedLineEnable = false;

			l_hr = m_device->CreateRasterizerState(&desc, &m_rasterizerState);
			if (FAILED(l_hr))
			{
				return l_hr;
			}

			m_deviceContext->RSSetState(m_rasterizerState);

			return l_hr;
		}

		HRESULT DirectXEngine::SetBlendState()
		{			
			HRESULT l_hr = S_OK;
			D3D11_BLEND_DESC l_blendStateDesc;
			l_blendStateDesc.AlphaToCoverageEnable			= false;
			l_blendStateDesc.IndependentBlendEnable			= false;

			l_blendStateDesc.RenderTarget[0].BlendEnable	= true;
			l_blendStateDesc.RenderTarget[0].SrcBlend		= D3D11_BLEND_SRC_ALPHA;
			l_blendStateDesc.RenderTarget[0].DestBlend		= D3D11_BLEND_INV_SRC_ALPHA;
			l_blendStateDesc.RenderTarget[0].BlendOp		= D3D11_BLEND_OP_ADD;
			l_blendStateDesc.RenderTarget[0].SrcBlendAlpha	= D3D11_BLEND_ONE;
			l_blendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
			l_blendStateDesc.RenderTarget[0].BlendOpAlpha	= D3D11_BLEND_OP_ADD;
			l_blendStateDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

			l_hr = m_device->CreateBlendState(&l_blendStateDesc, &m_blendState);
			if (FAILED(l_hr))
			{
				return l_hr;
			}

			float l_blendFactor[] = {0.0f, 0.0f, 0.0f, 0.0f};
			m_deviceContext->OMSetBlendState(m_blendState, l_blendFactor, 0xffffffff);
		}

		HRESULT DirectXEngine::CreateBuffer()
		{
			HRESULT l_hr = S_OK;

			D3D11_BUFFER_DESC bufferDesc;
			bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			bufferDesc.Usage	 = D3D11_USAGE_DEFAULT;
			bufferDesc.CPUAccessFlags = 0;
			bufferDesc.MiscFlags = 0;
			bufferDesc.ByteWidth = sizeof(DirectX::XMFLOAT4X4);
			l_hr = m_device->CreateBuffer(&bufferDesc, nullptr, &m_perFrameBuffer);
			if (FAILED(l_hr))
			{
				return l_hr;
			}

			bufferDesc.ByteWidth = sizeof(DirectX::XMFLOAT4);
			l_hr = m_device->CreateBuffer(&bufferDesc, nullptr, &m_perTextureBuffer);
			if (FAILED(l_hr))
			{
				return l_hr;
			}
			
			bufferDesc.ByteWidth = sizeof(DirectX::XMFLOAT4);
			l_hr = m_device->CreateBuffer(&bufferDesc, nullptr, &m_perWindowChangeBuffer);
			if (FAILED(l_hr))
			{
				return l_hr;
			}

			bufferDesc.BindFlags				= D3D11_BIND_VERTEX_BUFFER;
			bufferDesc.Usage					= D3D11_USAGE_DYNAMIC;
			bufferDesc.CPUAccessFlags			= D3D11_CPU_ACCESS_WRITE;
			bufferDesc.ByteWidth				= sizeof(Vertex) * 300000; // LOL fix this maybe
			l_hr = m_device->CreateBuffer(&bufferDesc, nullptr, &m_vertexBuffer);
			if (FAILED(l_hr))
			{
				return l_hr;
			}
			
			UINT stride = sizeof(Vertex);
			UINT offset = 0;
			m_deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

			m_deviceContext->GSSetConstantBuffers(0, 1, &m_perFrameBuffer);			// maybe fix array? yes
			m_deviceContext->GSSetConstantBuffers(1, 1, &m_perTextureBuffer);
			m_deviceContext->VSSetConstantBuffers(2, 1, &m_perWindowChangeBuffer);

			DirectX::XMFLOAT4 PerWindowChange = DirectX::XMFLOAT4(static_cast<float>(m_clientWidth), static_cast<float>(m_clientHeight), 0, 0);
			m_deviceContext->UpdateSubresource(m_perWindowChangeBuffer, 0, nullptr, &PerWindowChange, 0, 0); // UPDATE

		}

		HRESULT DirectXEngine::LoadShaders()
		{
			HRESULT l_hr;
			l_hr = m_shaderLoader->CreateGeometryShader(L"GeometryShader.hlsl", "GS", "gs_5_0", m_device, &m_geometryShader);
			l_hr = m_shaderLoader->CreatePixelShader(L"PixelShader.hlsl", "PS", "ps_5_0", m_device, &m_pixelShader);

			D3D11_INPUT_ELEMENT_DESC l_desc[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "ORIGIN", 0, DXGI_FORMAT_R32G32_FLOAT,			0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "OFFSET", 0, DXGI_FORMAT_R32G32_FLOAT,			0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "TEXTURE_OFFSET", 0, DXGI_FORMAT_R32G32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "ROTATION", 0, DXGI_FORMAT_R32_FLOAT,				0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "TEXTUREDELTA", 0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "FLIP", 0, DXGI_FORMAT_R32_UINT,					0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
			};
			unsigned int l_numElements = ARRAYSIZE(l_desc);
			l_hr = m_shaderLoader->CreateVertexShaderWithInputLayout(L"VertexShader.hlsl", "VS", "vs_5_0", m_device, &m_vertexShader, l_desc, l_numElements, &m_inputLayout);
			if (FAILED(l_hr))
			{
				return l_hr;
			}

			m_deviceContext->VSSetShader(m_vertexShader,	nullptr, 0);
			m_deviceContext->PSSetShader(m_pixelShader,		nullptr, 0);
			m_deviceContext->GSSetShader(m_geometryShader,	nullptr, 0);
			m_deviceContext->IASetInputLayout(m_inputLayout);	
			m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
			
			D3D11_SAMPLER_DESC sampler_desc;
			ZeroMemory(&sampler_desc, sizeof(sampler_desc));
			sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
			sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			sampler_desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
			sampler_desc.MinLOD = 0;
			sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;

			l_hr = m_device->CreateSamplerState(&sampler_desc, &m_samplerState);
			if (FAILED(l_hr))
			{
				return l_hr;
			}
			m_deviceContext->PSSetSamplers(0, 1, &m_samplerState);
			return l_hr;
		}
		
		ErrorMessage DirectXEngine::LoadTexture(Texture2DInterface** p_texture2DInterface, char* p_filePath)
		{
			return m_texture2DManager->GetTexture(p_texture2DInterface, p_filePath);
		}
	
		void DirectXEngine::Render(Point p_position,
			Point p_origin,
			Point p_textureOffset,
			Texture2DInterface* p_texture,
			SpriteEffect p_spriteEffect,
			float p_width,
			float p_height,
			float p_depth,
			float p_rotation,
			bool p_hasTransparent,
			Point p_textureDelta)
		{
			m_renderData.push_back(SpriteData(p_position, p_origin, p_textureOffset, (Texture2D*)p_texture, p_spriteEffect, p_width, p_height, p_depth, p_rotation, p_hasTransparent, p_textureDelta));
		}

		void DirectXEngine::Render(
			Point p_position,
			Point p_origin,
			Point p_textureOffset,
			Texture2DInterface* p_texture,
			float p_width,
			float p_height,
			float p_depth,
			float p_rotation) 
		{
			m_renderData.push_back(SpriteData(p_position, p_origin, p_textureOffset, (Texture2D*)p_texture, p_width, p_height, p_depth, p_rotation));
		}

		void DirectXEngine::Render(Point p_position,
			Point p_textureOffset,
			Texture2DInterface* p_texture,
			float p_width,
			float p_height,
			float p_depth)
		{
			m_renderData.push_back(SpriteData(p_position, p_textureOffset, (Texture2D*)p_texture, p_width, p_height, p_depth));
		}

		void DirectXEngine::Render(Point p_position, Point p_textureOffset,
			Texture2DInterface* p_texture,
			SpriteEffect p_spriteEffect,
			float p_width,
			float p_height,
			float p_depth)
		{
			m_renderData.push_back(SpriteData(p_position, p_textureOffset, (Texture2D*)p_texture, p_spriteEffect, p_width, p_height, p_depth));
		}
		
		void DirectXEngine::PostRender(Camera* p_camera)
		{
			int max = m_renderData.size() - 1;
			if (max < 0)
			{
				m_swapChain->Present(0, 0);
				return; // DO NOTHING
			}
				

			// Sort sprites after textures
			SortSprites();		

			Vertex* a = new Vertex[max + 1];

			for (int i = 0; i < max + 1; i++)
			{
				m_renderData[i].position -= p_camera->position;
				a[i] = Vertex(m_renderData[i]);
			}

			D3D11_MAPPED_SUBRESOURCE mappedResource;
			m_deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
			memcpy(mappedResource.pData, a, (max+1) * sizeof(Vertex));
			m_deviceContext->Unmap(m_vertexBuffer, 0);
			delete[] a;
			
			
			m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
			m_deviceContext->ClearRenderTargetView(m_backBuffer_RTV, DirectX::Colors::Black);

			// Update per frame buffer
			m_deviceContext->UpdateSubresource(m_perFrameBuffer, 0, nullptr, &m_view, 0, 0); // Transposse?
			
			unsigned int l_currentIndex = 0;
			unsigned int l_amount = 1;
			for ( int i = 0; i < max; i++)
			{
				if (m_renderData[i].texture == m_renderData[i + 1].texture)
					l_amount++;
				else
				{
					ID3D11ShaderResourceView* a = m_renderData[i].texture->GetShaderResourceView();	// change name
					m_deviceContext->PSSetShaderResources(0, 1, &a);

					DirectX::XMFLOAT4 PerTexture = DirectX::XMFLOAT4(1.0f, 1.0f, 0, 0);
					m_deviceContext->UpdateSubresource(m_perTextureBuffer, 0, nullptr, &PerTexture, 0, 0); // UPDATE
	
					m_deviceContext->Draw(l_amount,l_currentIndex);
					l_currentIndex += l_amount;
					l_amount = 1;
				}	
			}
			ID3D11ShaderResourceView* b = m_renderData[l_currentIndex].texture->GetShaderResourceView();	// change name
			m_deviceContext->PSSetShaderResources(0, 1, &b);

			DirectX::XMFLOAT4 PerTexture = DirectX::XMFLOAT4(1.0f, 1.0f, 0, 0);
			m_deviceContext->UpdateSubresource(m_perTextureBuffer, 0, nullptr, &PerTexture, 0, 0); // UPDATE
			m_deviceContext->Draw(l_amount, l_currentIndex);			


			m_swapChain->Present(0, 0);
			m_renderData.clear();
		}

		bool SortTransparentAlgorithm(SpriteData p_a, SpriteData p_b)
		{
			/*
				if p_a has transparent and p_b has transparent = > ok

				if p_a has transparent and p_b hasn't transparent = > false

				if p_a hasn't transparent and p_b has transparent => ok

				if p_a hasn't transaprent and p_b hasn't transparent => ok
			*/
			if (p_a.hasTransparent && p_b.hasTransparent)
			{
				return false;
			}
			else if(p_a.hasTransparent && !p_b.hasTransparent)
			{
				return true;
			}
			else if(!p_a.hasTransparent && p_b.hasTransparent)
			{
				return false;
			}
			else 
			{
				return false;
			}

			/*return (p_a.hasTransparent && !p_b.hasTransparent);*/
		}
		bool SortTextureAlgorithm(SpriteData p_a, SpriteData p_b)
		{
			return (p_a.texture < p_b.texture);
		}
		bool SortDepthAlgorithm(SpriteData p_a, SpriteData p_b)
		{
			return (p_a.depth > p_b.depth);
		}
		
		void DirectXEngine::SortSprites()
		{	
			//std::sort(m_renderData.begin(), m_renderData.end(), &SortTransparentAlgorithm);
			int size = m_renderData.size() - 1;
			bool NOTWORKING = TRUE;
			while (NOTWORKING)
			{
				NOTWORKING = false;
				for (int i = 0; i < size; i++)
				{
					if (SortTransparentAlgorithm(m_renderData[i], m_renderData[i+1]))
					{
						SpriteData temp = m_renderData[i];
						m_renderData[i] = m_renderData[i + 1];
						m_renderData[i + 1] = temp;
						NOTWORKING = true;
					}
				}
			}
			
			int transparentStart = 0;
			for (int i = 0; i < size + 1; i++)
			{
				if (m_renderData[i].hasTransparent)
				{
					transparentStart = i;
					i = size + 1;
				}
			}
			std::sort(m_renderData.begin(), m_renderData.begin() + transparentStart, &SortTextureAlgorithm);
			std::sort(m_renderData.begin() + transparentStart, m_renderData.end(), &SortDepthAlgorithm);
		}
	}
}