#pragma once
#include "../Vector/Vector3.h"

//******************************
// Better than matrices (sometimes ;))
// --> No Gimbal lock
// --> Less memory and faster computation
//******************************

// https://www.haroldserrano.com/blog/developing-a-math-engine-in-c-implementing-quaternions
//

namespace Libero
{
	using Vector3f = Vector<float, 3>;
	struct Quaternion final
	{
	public:
#pragma warning(disable : 4201)
		union
		{
			struct { float s, i, j, k; };
			struct { float s; Libero::Vector3f v; };
			float data[4];
		};
#pragma warning(default : 4201)

		Quaternion();
		Quaternion(float s, const Vector3f& v);
		
#pragma region Quaternion
		float Norm() const;
		float Magnitude() const;
		static float Norm(const Quaternion& q);
		static float Magnitude(const Quaternion& q);

		Quaternion Normalized() const;
		void Normalize();
		static Quaternion Normalized(const Quaternion& q);
		static void Normalize(Quaternion& q);

		void ToUnitNorm();
		Quaternion UnitNorm() const;
		static void ToUnitNorm(Quaternion& q);
		static Quaternion UnitNorm(const Quaternion& q);

		Quaternion Conjugate() const;
		static Quaternion Conjugate(const Quaternion& q);

		Quaternion Inverted() const;
		void Inverse();
		static Quaternion Inverted(const Quaternion& q);
		static void Inverse(Quaternion& q);
#pragma endregion

		Vector3f RotateVectorAxis(float angle, const Vector3f& v, const Vector3f& axis) const;

		void operator+=(const Quaternion& q);
		void operator-=(const Quaternion& q);
		void operator*=(const Quaternion& q);
		void operator*=(const float& scalar);
	};
	Quaternion operator+(const Quaternion& qA, const Quaternion& qB);
	Quaternion operator-(const Quaternion& qA, const Quaternion& qB);
	Quaternion operator*(const Quaternion& qA, const Quaternion& qB);
}


