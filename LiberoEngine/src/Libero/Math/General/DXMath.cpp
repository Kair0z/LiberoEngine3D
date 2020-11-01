#include "Liber_pch.h"
#include "DXMath.h"

namespace Libero
{
	namespace Math
	{
		ColorRGBA WithAlpha(const ColorRGB& col, float a)
		{
			return ColorRGBA({ col.x, col.y, col.z, a });
		}

		XMVECTOR ToXMVector(const XMFLOAT3& t)
		{
			return XMLoadFloat3(&t);
		}

		XMVECTOR ToXMVector(const Vector3f& v)
		{
			XMFLOAT3 t{ v.x, v.y, v.z };
			return ToXMVector(t);
		}

		XMVECTOR ToXMVector(const XMFLOAT4& t)
		{
			return XMLoadFloat4(&t);
		}

		XMVECTOR ToXMVector(const Vector4f& v)
		{
			XMFLOAT4 t{ v.x, v.y, v.z, v.w };
			return ToXMVector(t);
		}

		XMVECTOR ToXMVector(const XMFLOAT2& t)
		{
			return XMLoadFloat2(&t);
		}

		XMVECTOR ToXMVector(const Vector2f& v)
		{
			XMFLOAT2 t{ v.x, v.y };
			return ToXMVector(t);
		}

		XMFLOAT3 ToXMFLOAT3(const XMVECTOR& v)
		{
			XMFLOAT3 res{};
			XMStoreFloat3(&res, v);

			return res;
		}

		XMFLOAT2 ToXMFLOAT2(const XMVECTOR& v)
		{
			XMFLOAT2 res{};
			XMStoreFloat2(&res, v);
			return res;
		}

		XMFLOAT4 toXMFLOAT4(const XMVECTOR& v)
		{
			XMFLOAT4 res{};
			XMStoreFloat4(&res, v);
			return res;
		}
	}
}