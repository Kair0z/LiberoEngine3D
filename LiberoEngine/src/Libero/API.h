#pragma once

#ifdef LBR_DLL
	#define LBR_API __declspec(dllexport)
#else
	#define LBR_API __declspec(dllimport)
#endif
