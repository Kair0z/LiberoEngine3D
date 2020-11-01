#pragma once
#include "../LiberoMath.h"
#include <DirectXMath.h>
using namespace DirectX;

namespace Libero
{
	namespace Math
	{
		ColorRGBA WithAlpha(const ColorRGB& col, float a);

		XMVECTOR ToXMVector(const XMFLOAT3& t);
		XMVECTOR ToXMVector(const Vector3f& v);
		XMVECTOR ToXMVector(const XMFLOAT4& t);
		XMVECTOR ToXMVector(const Vector4f& v);
		XMVECTOR ToXMVector(const XMFLOAT2& t);
		XMVECTOR ToXMVector(const Vector2f& v);
		XMFLOAT3 ToXMFLOAT3(const XMVECTOR& v);
		XMFLOAT2 ToXMFLOAT2(const XMVECTOR& v);
		XMFLOAT4 toXMFLOAT4(const XMVECTOR& v);
	}
}