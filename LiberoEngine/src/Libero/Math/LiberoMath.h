#pragma once

#include "2D/2DMath.h"
#include "3D/3DMath.h"
#include "Vector/Vector.h"
#include "Quaternion/Quaternion.h"
#include "Matrix/Matrix.h"
#include "General/DXMath.h"
#include "Random/Random.h"
#include "Space/Space.h"

namespace Libero
{
	namespace Math
	{
		inline float Pi() { return 3.1415926535897932384626433f; }

		template <typename T>
		inline T ToRadians(const T degrees)
		{
			return (T)(degrees * (Pi() / 180.0f));
		}

		template <typename T>
		inline T ToDegrees(const T radians)
		{
			return (T)(radians * (180.0f / Pi()));
		}

		template <typename T>
		inline T Round(const T value)
		{
			return (T)std::round(value);
		}

		template <typename T>
		inline T Ceil(const T value)
		{
			return (T)std::ceil(value);
		}

		template <typename T>
		inline T Floor(const T value)
		{
			return (T)std::floor(value);
		}
	}
}