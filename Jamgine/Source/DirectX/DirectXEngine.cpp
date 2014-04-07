#include <Jamgine/Include/DirectX/DirectXEngine.h>
#include <Jamgine/Include/DirectX/DirectXShared.h>
#include <exception>

namespace Jamgine
{
	namespace DirectX
	{		
		DirectXEngine::DirectXEngine()
			: m_device(nullptr), m_context(nullptr)
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
			try
			{
//				RegisterWindow(p_data);
			}
			catch (std::exception e) 
			{
				return J_FAIL; 
			}

			try
			{
				InitializeSwapChain();
			}
			catch (std::exception e)
			{
				return J_FAIL;
			}

//			*p_data.handle = &m_handle;

			return l_errorMessage;
		}

		void DirectXEngine::Render(Position p_position, SpriteEffect::SpriteEffect p_spriteEffect)
		{
			
		}

	ErrorMessage DirectXEngine::RegisterWindow()
	{
		ErrorMessage l_errorMessage = J_OK;

		WNDCLASSEX l_wndClass;
		l_wndClass.style         = CS_HREDRAW | CS_VREDRAW;
		l_wndClass.lpfnWndProc   = MainWndProc; 
		l_wndClass.cbClsExtra    = 0;
		l_wndClass.cbWndExtra    = 0;
		l_wndClass.hInstance     = m_hInstance;
		l_wndClass.hIcon         = LoadIcon(0, IDI_APPLICATION);
		l_wndClass.hCursor       = LoadCursor(0, IDC_ARROW);
		l_wndClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
		l_wndClass.lpszMenuName  = 0;
		l_wndClass.lpszClassName = L"D3DWndClassName";
			
		if (!RegisterClassEx(&l_wndClass))
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
			m_hInstance, 
			NULL);
		if(m_handle == NULL)
			return J_FAIL;

		return l_errorMessage;
	}
		

		void DirectXEngine::InitializeSwapChain()
		{

		}
	}
}