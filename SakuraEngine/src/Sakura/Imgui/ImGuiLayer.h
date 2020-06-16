#pragma once

#include "Sakura/skpch.h"
#include "Sakura/Core.h"
#include "Sakura/Application.h"
#include "Sakura/Events/Event.h"
#include "Sakura/Events/ApplicationEvent.h"
#include "Sakura/Events/MouseEvent.h"
#include "Sakura/Events/KeyEvent.h"
#include "Sakura/Layer.h"

namespace Sakura
{
	class SAKURA_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	private:	
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
	};
}

