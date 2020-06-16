#pragma once
#include "Core.h"
#include "Sakura/Events/Event.h"

namespace Sakura
{
	class SAKURA_API Layer
	{
	public:
		Layer() {};
		virtual ~Layer() {}

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}
	};
}

