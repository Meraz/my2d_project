#include <Jamgine/Include/DirectX/DirectXEngine.h>
#include <Jamgine/Include/DirectX/DirectXShared.h>
#include <DirectX/D3D11.h>
#include <exception>

namespace Jamgine
{
	namespace DirectX
	{		
		DirectXEngine::DirectXEngine()
			: m_device(nullptr), m_deviceContext(nullptr)
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
			catch (exception e)
			{
				return J_FAIL;
			}
			l_errorMessage = Initialize(l_data);
			return l_errorMessage;
		}

		ErrorMessage DirectXEngine::Initialize(Jamgine::Data_Send p_data)
		{
			ErrorMessage l_errorMessage = J_OK;

			m_hInstance		=	p_data.hInstance;
			m_clientWidth = p_data.clientWidth;
			m_clientHeight = p_data.clientHeight;
//			try
//			{
				RegisterWindow(p_data);
//			}
//			catch (std::exception e) 
//			{
//				return J_FAIL; 
//			}

			l_errorMessage = InitializeSwapChain();
			if(l_errorMessage != J_OK)
				return J_FAIL; 


			return l_errorMessage;
		}

		void DirectXEngine::Render(Position p_position, SpriteEffect::SpriteEffect p_spriteEffect)
		{
			//m_swapChain->Present(0, 0);
		}

		void DirectXEngine::PostRender()
		{
			m_swapChain->Present(0, 0);
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
	//			l_swapChainDesc.BufferDesc.ScanlineOrdering			= DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	//			l_swapChainDesc.BufferDesc.Scaling					= DXGI_MODE_SCALING_UNSPECIFIED;
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