#pragma once
#include "Libero/Math/LiberoMath.h"
#include <string>
#include <Windows.h>

struct IDXGIAdapter;
struct IDXGIOutput;

namespace Libero
{
	struct WindowSettings
	{
		static Vector2f Dimensions;
		static float AR;
		static std::string Title;
		static HWND Handle;
	};

	struct DXSettings
	{
		IDXGIAdapter* pAdapter = nullptr;
		IDXGIOutput* pOutput = nullptr;
	};

	struct GameSettings
	{

	};

	struct Settings
	{
		static WindowSettings Window;
		static DXSettings DX;
		static GameSettings Game;
	};
}