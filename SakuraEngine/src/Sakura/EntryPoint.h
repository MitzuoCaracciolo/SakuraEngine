#pragma once

#ifdef SAKURA_PLATAFORM_WINDOWS

extern Sakura::Application* Sakura::CreateApplication();

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	FILE* fp;
	AllocConsole();
	freopen_s(&fp, "CONIN$", "r", stdin);
	freopen_s(&fp, "CONOUT$", "w", stdout);
	Sakura::Application* app = Sakura::CreateApplication();
	app->Run();
	delete app;
}

#endif