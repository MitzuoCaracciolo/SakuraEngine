#pragma once

#ifdef SAKURA_PLATAFORM_WINDOWS
	#ifdef SAKURA_BUILD_DLL
		#define SAKURA_API __declspec(dllexport)
	#else 
		#define SAKURA_API __declspec(dllimport)
	#endif
#else
	#error Only supported on Windows
#endif

#define BIT(x) (1 << x)
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)