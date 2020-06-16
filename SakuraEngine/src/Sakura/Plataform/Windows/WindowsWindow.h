#ifdef SAKURA_PLATAFORM_WINDOWS
#pragma once
#include "Sakura/skpch.h"

#include "Sakura/Window.h"
#include "Sakura/Events/KeyEvent.h"
#include "Sakura/Events/MouseEvent.h"
#include "Sakura/Events/ApplicationEvent.h"

namespace Sakura
{
	class SAKURA_API WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow() override;

		virtual void OnUpdate() override;

		inline virtual void* GetHandle() override { return m_Hwnd; }
		inline virtual unsigned int GetWidth() override { return m_Width; }
		inline virtual unsigned int GetHeight() override { return m_Height; }

		void SetEventCallback(const EventCallbackFn& callback) override { EventCallback = callback; }

	private:
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		virtual void Init(const WindowProps& props);
		virtual void ShutDown();

	private:
		HWND m_Hwnd;
		HGLRC RenderingContext;
		HDC DeviceContext;
		EventCallbackFn EventCallback;
		unsigned int m_Width;
		unsigned int m_Height;
		bool m_Closed;
	};
}

#endif
