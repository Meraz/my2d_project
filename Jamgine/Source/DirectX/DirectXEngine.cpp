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

			m_handle		=	p_data.l_handle;
			m_hInstance		=	p_data.l_hInstance;
			try
			{
				RegisterWindow(p_data);
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

			return l_errorMessage;
		}

		void DirectXEngine::Render(Position p_position, SpriteEffect::SpriteEffect p_spriteEffect)
		{
			
		}

		ErrorMessage DirectXEngine::RegisterWindow(Jamgine::Data_Send p_data)
		{
			ErrorMessage l_errorMessage = J_OK;

			WNDCLASS l_wndclass;
			l_wndclass.style = CS_HREDRAW | CS_VREDRAW;
			l_wndclass.lpfnWndProc = p_data.WNDPROC;
			l_wndclass.cbClsExtra = 0;
			l_wndclass.cbWndExtra = 0;
			l_wndclass.hInstance = p_data.l_hInstance;
			l_wndclass.hIcon = 0;
			l_wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
			l_wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			l_wndclass.lpszMenuName = NULL;
			l_wndclass.lpszClassName = L"TestGame";
			
			if (!RegisterClass(&l_wndclass))
				return J_FAIL;

				
			// Create window
			RECT rc = { 0, 0, p_data.p_clientWidth, p_data.p_clientHeight };
			//AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

			if (!CreateWindow(L"TestGame", L"Welcome to this window",
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, CW_USEDEFAULT,
				rc.right - rc.left,
				rc.bottom - rc.top,
				NULL, NULL, p_data.l_hInstance, NULL))
			{
				return J_FAIL;
			}
			return l_errorMessage;
		}

		void DirectXEngine::InitializeSwapChain()
		{

		}
	}
}