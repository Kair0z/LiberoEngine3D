#pragma once
#include "../Vector/Vector.h"

#pragma warning(disable: 4201)
namespace Libero
{
	namespace Math
	{
		struct Sphere
		{
			union
			{
				struct { Vector<float, 3> center; float radius; };
				struct { float x, y, z, r; };
			};

			Sphere(const Vector<float, 3>& center, float radius);
		};
	}
}
#pragma warning(default: 4201)


