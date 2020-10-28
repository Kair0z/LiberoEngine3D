#pragma once
#include "Libero/Math/LiberoMath.h"

namespace Libero
{
	class DebugRenderer
	{
	public:
		void DrawLine(const Vector3f& p0, const Vector3f& p1, const Color& col) const;
	};
}


