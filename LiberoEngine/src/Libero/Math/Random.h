#pragma once
#include <random>
#include "Libero/Math/LiberoMath.h"

namespace Libero
{
	namespace Random
	{
		template <typename T>
		inline T Rand(const T& min, const T& max)
		{
			T range = max - min;
			return rand() % range + min;
		}

		inline float Rand(const float&, const float& max)
		{
			return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / max));
		}

		inline double Rand(const double&, const double& max)
		{
			return static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / max));
		}


		inline Color ColorRand()
		{
			return { Rand(0.0f, 1.0f), Rand(0.0f, 1.0f), Rand(0.0f, 1.0f) };
		}
	}
}