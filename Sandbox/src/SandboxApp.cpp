#pragma once
#include <Sakura.h>

class SandboxApp : public Sakura::Application
{
public:
	SandboxApp()
	{
		PushOverlay(new Sakura::ImGuiLayer());
	}
	~SandboxApp()
	{

	}
};

Sakura::Application* Sakura::CreateApplication()
{
	return new SandboxApp();
}