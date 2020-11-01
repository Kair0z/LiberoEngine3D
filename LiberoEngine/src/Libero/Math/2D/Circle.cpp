#include "Circle.h"

namespace Libero
{
	namespace Math
	{
		inline Circle::Circle(const Vector<float, 2>& _center, float _radius) : center{ _center }, radius{ _radius }{};
	}
}