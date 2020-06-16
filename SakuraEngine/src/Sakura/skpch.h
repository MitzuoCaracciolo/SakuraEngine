#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <vector>

#include "glad/glad.h"
#include "imgui.h"

#ifdef SAKURA_PLATAFORM_WINDOWS
#include <Windows.h>
#include <Windowsx.h>
#include "Sakura/Plataform/Windows/imgui_impl_win32.h"
#endif

#include "Sakura/Plataform/OpenGL/imgui_impl_opengl3.h"