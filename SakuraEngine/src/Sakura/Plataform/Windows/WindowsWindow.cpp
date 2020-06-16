#ifdef SAKURA_PLATAFORM_WINDOWS

#include "WindowsWindow.h"

namespace Sakura
{
	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) : m_Closed(false)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		ShutDown();
	}

	void WindowsWindow::OnUpdate()
	{
		MSG message;
		while (PeekMessage(&message, NULL, NULL, NULL, PM_REMOVE) > 0)
		{
			if (message.message == WM_QUIT)
			{
				m_Closed = true;
				return;
			}
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		SwapBuffers(DeviceContext);
	}

	LRESULT WindowsWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		WindowsWindow* pThis = nullptr;
		if (uMsg == WM_NCCREATE)
		{
			CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
			pThis = (WindowsWindow*)pCreate->lpCreateParams;
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);
		}
		else
		{
			LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
			pThis = reinterpret_cast<WindowsWindow*>(ptr);
		}

		switch (uMsg)
		{
			case WM_KEYDOWN:
			{
				KeyPressedEvent event(wParam, 0);
				pThis->EventCallback(event);
				return 0;
			}
			case WM_KEYUP:
			{
				KeyReleasedEvent event(wParam);
				pThis->EventCallback(event);
				return 0;
			}
			case WM_CHAR:
			{
				KeyTypedEvent event(wParam);
				pThis->EventCallback(event);
				return 0;
			}
			case WM_MOUSEMOVE:
			{
				MouseMovedEvent event(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				pThis->EventCallback(event);
				return 0;
			}
			case WM_LBUTTONDOWN:
			case WM_RBUTTONDOWN:
			{
				int button = 0;
				if(uMsg == WM_RBUTTONDOWN)
					button = 1;
				MouseButtonPressedEvent event(button);
				pThis->EventCallback(event);
				return 0;
			}
			case WM_LBUTTONUP:
			case WM_RBUTTONUP:
			{
				int button = 0;
				if (uMsg == WM_RBUTTONUP)
					button = 1;
				MouseButtonReleasedEvent event(button);
				pThis->EventCallback(event);
				return 0;
			}
			case WM_CLOSE:
			{
				WindowCloseEvent event;
				pThis->EventCallback(event);
				return DefWindowProc(hwnd, uMsg, wParam, lParam);
			}
			case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			}
		}
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Width = props.Width;
		m_Height = props.Height;

		WNDCLASS wc = {};
		wc.lpfnWndProc = WindowsWindow::WindowProc;
		wc.hInstance = GetModuleHandle(nullptr);
		wc.lpszClassName = L"Sakura Win32";
		wc.style = CS_OWNDC;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);

		RegisterClass(&wc);

		RECT rect = { 0, 0, (LONG)props.Width, (LONG)props.Height };
		AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, FALSE, 0);

		m_Hwnd = CreateWindowEx(
			0,
			wc.lpszClassName,
			(wchar_t*)props.Title,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			props.Width,
			props.Height,
			nullptr,
			nullptr,
			GetModuleHandle(nullptr),
			this
		);

		
		PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
			PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
			32,                   // Colordepth of the framebuffer.
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24,                   // Number of bits for the depthbuffer
			8,                    // Number of bits for the stencilbuffer
			0,                    // Number of Aux buffers in the framebuffer.
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};

		DeviceContext = ::GetDC(m_Hwnd);
		int PixelFormat = ChoosePixelFormat(DeviceContext, &pfd);
		SetPixelFormat(DeviceContext, PixelFormat, &pfd);
		RenderingContext = wglCreateContext(DeviceContext);
		wglMakeCurrent(DeviceContext, RenderingContext);
		gladLoadGL();
		ShowWindow(m_Hwnd, SW_SHOW);
	}

	void WindowsWindow::ShutDown()
	{
		wchar_t className[128];
		unsigned int count = 0;
		GetClassName(m_Hwnd, className, count);
		UnregisterClass(className, GetModuleHandle(nullptr));
		wglMakeCurrent(DeviceContext, nullptr);
		wglDeleteContext(RenderingContext);
		ReleaseDC(m_Hwnd, DeviceContext);
	}
}

#endif