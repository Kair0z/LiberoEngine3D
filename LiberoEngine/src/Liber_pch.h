#pragma once
// Windows:
#include <Windows.h>
#include <windowsx.h>

// VLD:
#include "vld.h"

// ImGui:
#include "Libero/Editor/ImGui/imgui.h"
#include "Libero/Editor/ImGui/imgui_impl_win32.h"
#include "Libero/Editor/ImGui/imgui_impl_dx11.h"

// DX:
#include <dxgi.h>
#include <d3d11.h>
#include "DirectXTex.h"
#include "d3dx11effect.h"

#pragma comment( lib, "d3d11.lib" )       // direct3D library
#pragma comment( lib, "dxgi.lib" )        // directx graphics interface
#pragma comment( lib, "d3dcompiler.lib" ) // shader compiler

#include "WICTextureLoader.h"
#pragma comment (lib, "DirectXTK.lib")

// DXMath:
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <DirectXPackedVector.h>
#include <DirectXCollision.h>

// STL:
#include <iostream>
#include <vector>
#include <unordered_map>
#include <deque>
#include <list>
#include <array>
#include <fstream>
#include <memory>
#include <algorithm>
#include <string>
#include <functional>
#include <unordered_set>
#include <sstream>
#include <cassert>

// LiberoMath:
#include "Libero/Math/LiberoMath.h"

// LiberoUtils:
#include "Libero/Misc/LiberoUtils.h"