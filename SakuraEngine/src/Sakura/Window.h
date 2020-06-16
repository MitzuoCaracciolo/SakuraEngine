#pragma once
#include "Sakura/skpch.h"
#include "Sakura/Core.h"
#include "Sakura/Events/Event.h"

namespace Sakura
{

	struct SAKURA_API WindowProps
	{
		wchar_t Title[128];
		unsigned int Width;
		unsigned int Height;

		WindowProps(const wchar_t* title = L"Sakura Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Width(width), Height(height)
		{
			wcscpy_s(Title, 128, title);
		}
	};

	class SAKURA_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		
		virtual ~Window() {}

		virtual void OnUpdate() = 0;
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		virtual void* GetHandle() = 0;
		virtual unsigned int GetWidth() = 0;
		virtual unsigned int GetHeight() = 0;


		static Window* Create(const WindowProps& props = WindowProps());
	};
}