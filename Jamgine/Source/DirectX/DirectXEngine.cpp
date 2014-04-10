// Official libs
#include <exception>
#include <algorithm>  


// Project files
#include <Jamgine/Include/DirectX/DirectXEngine.h>
#include <Jamgine/Include/DirectX/DirectXShared.h>

namespace Jamgine
{
	namespace DirectX
	{		

		DirectXEngine::DirectXEngine()
			: m_device(nullptr), m_deviceContext(nullptr), m_texture2DManager(nullptr)
		{

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
			LoadShaders();

			return l_errorMessage;
		}

		void DirectXEngine::InitializeRenderTarget()
		{
			HRESULT hr;
			ID3D11Texture2D* l_backBuffer;
			hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&l_backBuffer);
			hr = m_device	->CreateRenderTargetView(l_backBuffer, nullptr, &m_backBuffer_RTV);
			hr = m_device	->CreateUnorderedAccessView(l_backBuffer, nullptr, &m_backBuffer_UAV);

			l_backBuffer->Release();
		}

		void DirectXEngine::CreateDepthBuffer()
		{
			HRESULT hr = S_OK;

			// Create depth stencil texture
			D3D11_TEXTURE2D_DESC descDepth;
			ZeroMemory(&descDepth, sizeof(descDepth));
			descDepth.Width = m_clientWidth;
			descDepth.Height = m_clientHeight;
			descDepth.MipLevels = 1;
			descDepth.ArraySize = 1;
			descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			descDepth.SampleDesc.Count = 1;
			descDepth.SampleDesc.Quality = 0;
			descDepth.Usage = D3D11_USAGE_DEFAULT;
			descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			descDepth.CPUAccessFlags = 0;
			descDepth.MiscFlags = 0;

			hr = m_device->CreateTexture2D(&descDepth, nullptr, &m_depthStencil);

			D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
			ZeroMemory(&descDSV, sizeof(descDSV));
			descDSV.Format = descDepth.Format;
			descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			descDSV.Texture2D.MipSlice = 0;
			hr = m_device->CreateDepthStencilView(m_depthStencil, &descDSV, &m_depthStencilView);

			//create states
			D3D11_DEPTH_STENCIL_DESC dsDesc;

			// Depth test parameters
			dsDesc.DepthEnable = true;
			dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			//dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
			dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

			// Stencil test parameters
			dsDesc.StencilEnable = true;	// YES?1
			dsDesc.StencilReadMask = 0xFF;
			dsDesc.StencilWriteMask = 0xFF;

			hr = m_device->CreateDepthStencilState(&dsDesc, &m_depthStencilState);
		}

		void DirectXEngine::LoadShaders()
		{
			/*
			m_shaderLoader->CreateGeometryShader(L"geometryshader.hlsl", "GS", "gs_5_0", m_device, &m_geometryShader);
			m_shaderLoader->CreatePixelShader(L"pixelshader.hlsl", "PS", "ps_5_0", m_device, &m_pixelShader);

			D3D11_INPUT_ELEMENT_DESC l_desc[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,		D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "ORIGIN", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,			D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "OFFSET", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,			D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{"ROTATION", 0,	DXGI_FORMAT_R32G32B32_FLOAT, 0,			D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{"ANIMATION_FLOAT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,	D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
			};

			unsigned int l_numElements = ARRAYSIZE(l_desc);
			m_shaderLoader->CreateVertexShaderWithInputLayout(L"vertexshader.hlsl", "VS", "vs_5_0", m_device, &m_vertexShader, l_desc, l_numElements, &m_inputLayout);

			m_deviceContext->VSSetShader(m_vertexShader,	nullptr, 0);
			m_deviceContext->PSSetShader(m_pixelShader,		nullptr, 0);
			m_deviceContext->GSSetShader(m_geometryShader,	nullptr, 0);
			m_deviceContext->IASetInputLayout(m_inputLayout);
			*/
		}


		ErrorMessage DirectXEngine::LoadTexture(Texture2DInterface** p_texture2DInterface, char* p_filePath)
		{
			return m_texture2DManager->GetTexture(p_texture2DInterface, p_filePath);
		}
		
		void DirectXEngine::Render(Position p_position, Texture2DInterface* p_textureInterface, SpriteEffect p_spriteEffect)
		{
			m_renderData.push_back(SpriteData(p_position, p_textureInterface, p_spriteEffect));
		}
		
		void DirectXEngine::PostRender()
		{
			SortSprites();

			//



			m_swapChain->Present(0, 0);
		}
		
		/*
		bool DirectXEngine::SortAlgorithm(SpriteData p_a, SpriteData p_b) 
		{
			return (p_a.texture < p_b.texture); 
		}
		*/
				
		bool SortAlgorithm(SpriteData p_a, SpriteData p_b)
		{
			return (p_a.texture < p_b.texture);
		}
		
		void DirectXEngine::SortSprites()
		{
			std::sort(m_renderData.begin(), m_renderData.end(), &SortAlgorithm);
		}

		ErrorMessage DirectXEngine::RegisterWindow(Jamgine::Data_Send p_data)
		{
			ErrorMessage l_errorMessage = J_OK;

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
				return J_FAIL;
							
			// Create window
			RECT rc = { 0, 0, m_clientHeight, m_clientWidth};
			//AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

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
				return J_FAIL;

			ShowWindow( m_handle, SW_SHOW);

			return l_errorMessage;
		}		

		ErrorMessage DirectXEngine::InitializeSwapChain()
		{
			ErrorMessage l_errorMessage = J_OK;

			DXGI_SWAP_CHAIN_DESC l_swapChainDesc;
			l_swapChainDesc.BufferDesc.Width					= m_clientWidth;
			l_swapChainDesc.BufferDesc.Height					= m_clientHeight;
			l_swapChainDesc.BufferDesc.RefreshRate.Numerator	= 60;
			l_swapChainDesc.BufferDesc.RefreshRate.Denominator	= 1;
			l_swapChainDesc.BufferDesc.Format					= DXGI_FORMAT_R8G8B8A8_UNORM;
			l_swapChainDesc.SampleDesc.Count					= 4;
			l_swapChainDesc.SampleDesc.Quality					= 1;
			l_swapChainDesc.BufferUsage							= DXGI_USAGE_RENDER_TARGET_OUTPUT;// | DXGI_USAGE_UNORDERED_ACCESS;
			l_swapChainDesc.BufferCount							= 1;
			l_swapChainDesc.OutputWindow						= m_handle;
			l_swapChainDesc.Windowed							= true;
			l_swapChainDesc.SwapEffect							= DXGI_SWAP_EFFECT_DISCARD;
			l_swapChainDesc.Flags								= 0;

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

			l_errorMessage = D3D11CreateDeviceAndSwapChain(
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

			return l_errorMessage;
		}
	}
}