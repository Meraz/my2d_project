// Official libs
#include <exception>

// Third parties libs included in this lib
#include <DirectX/D3D11.h>

// Project files
#include <Jamgine/Include/DirectX/DirectXEngine.h>
#include <Jamgine/Include/DirectX/DirectXShared.h>
#include <Jamgine/Include/DirectX/SpriteData.h>

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

			return l_errorMessage;
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
			// Sort everything up.
			m_swapChain->Present(0, 0);
		}
		
		void DirectXEngine::SortSprites()
		{
			for(unsigned int i = 0; i < m_renderData.size(); i++)
			{
				//m_renderData.
			}
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