#pragma once

#include "Sakura/skpch.h"
#include "Sakura/Core.h"
#include "Sakura/Window.h"

#include "Sakura/Layer.h"
#include "Sakura/LayerStack.h"

#include "Sakura/Events/Event.h"
#include "Sakura/Events/KeyEvent.h"
#include "Sakura/Events/MouseEvent.h"
#include "Sakura/Events/ApplicationEvent.h"

namespace Sakura
{
	class SAKURA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		static Application& Get() { return *s_Instance; }
		Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);	

	private:
		static Application* s_Instance;
		Window* m_Window;
		LayerStack m_LayerStack;

		bool m_Running = true;
	};

	Application* CreateApplication();
}

