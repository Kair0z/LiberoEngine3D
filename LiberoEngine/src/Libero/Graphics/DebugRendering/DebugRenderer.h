#pragma once
#include "Libero/Math/LiberoMath.h"

namespace Libero
{
	using namespace Math;
	class DebugRenderer
	{
	public:
		void DrawLine(const Vector3f& p0, const Vector3f& p1, const Color& col) const;
	};
}


