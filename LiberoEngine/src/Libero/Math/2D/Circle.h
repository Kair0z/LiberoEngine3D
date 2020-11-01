#pragma once
#include "../Vector/Vector.h"

#pragma warning(disable: 4201)
namespace Libero
{
	namespace Math
	{
		struct Circle
		{
			union
			{
				struct { T x, y, r; };
				struct { Vector<float, 2> center; float radius; };
			};

			Circle(const Vector<float, 2>& center, float radius);
		};
	}
}
#pragma warning(default: 4201)