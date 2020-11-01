#include "Liber_pch.h"
#include "Sphere.h"

namespace Libero
{
	namespace Math
	{
		inline Sphere::Sphere(const Vector<float, 3>& _center, float _radius) : center{ _center }, radius{ _radius }{}
	}
}