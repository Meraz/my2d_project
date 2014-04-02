#include <Jamgine/Include/DirectX/DirectXEngine.h>

namespace Jamgine
{
	namespace DirectX
	{
		
		DirectXEngine::DirectXEngine()
			: m_device(nullptr), m_context(nullptr), m_hInstance(nullptr), m_handle(nullptr)
		{

		}

		DirectXEngine::~DirectXEngine()
		{

		}

		ErrorMessage DirectXEngine::Initialize(void* p_data)
		{
			//HWND p_handle, HINSTANCE p_hInstance, int  p_clientWidth, int p_clientHeight
			ErrorMessage l_errorMessage = J_OK;


			return l_errorMessage;
		}

		void DirectXEngine::Render(Position p_position, SpriteEffect::SpriteEffect p_spriteEffect)
		{
			
		}


		void DirectXEngine::InitializeSwapChain()
		{

		}

		void DirectXEngine::RegisterWindow(HINSTANCE p_hInstance, LRESULT CALLBACK p_messageProcces(HWND, UINT, WPARAM, LPARAM))
		{
			WNDCLASS l_wndclass;
			l_wndclass.style = CS_HREDRAW | CS_VREDRAW;
			l_wndclass.lpfnWndProc = p_messageProcces;
			l_wndclass.cbClsExtra = 0;
			l_wndclass.cbWndExtra = 0;
			l_wndclass.hInstance = p_hInstance;
			l_wndclass.hIcon = 0;
			l_wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
			l_wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			l_wndclass.lpszMenuName = NULL;
			l_wndclass.lpszClassName = L"TestGame";
		}
	}
}