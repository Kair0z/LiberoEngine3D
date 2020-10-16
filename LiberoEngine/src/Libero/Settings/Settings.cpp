#include "Liber_pch.h"
#include "Settings.h"

namespace Libero
{
	// WindowSettings:
	Vector2f WindowSettings::Dimensions = { 1920.f, 1040.f };
	float WindowSettings::AR = WindowSettings::Dimensions.x / WindowSettings::Dimensions.y;
	static std::string Title = "The Libero Engine <DX11>";
	static HWND Handle;

	// All:
	DXSettings Settings::DX{};
	WindowSettings Settings::Window{};
	GameSettings Settings::Game{};
}