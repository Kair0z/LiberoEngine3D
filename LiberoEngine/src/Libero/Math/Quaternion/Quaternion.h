#pragma once
#include "../AVector/Vector.h"

//******************************
// Better than matrices (sometimes ;))
// --> No Gimbal lock
// --> Less memory and faster computation
//******************************

// https://www.haroldserrano.com/blog/developing-a-math-engine-in-c-implementing-quaternions

#pragma warning(disable : 4201)
namespace Libero
{
	struct Quaternion final
	{
	public:
		union
		{
			struct { float i, j, k, s; };
			struct { Vector3f v; float s; };
			float data[4];
		};

		Quaternion(float i = 0.0f, float j = 0.0f, float k = 0.0f, float s = 0.0f);
		Quaternion(const Vector3f& v, float s);
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
		
		Vector3f GetEulerAngles(bool round = false) const;

		Vector3f RotateVectorAxis(float angle, const Vector3f& v, const Vector3f& axis) const;
		
		static Quaternion MakeRotationFromTo(const Vector3f& from, const Vector3f& to, const Vector3f& up);
		static Quaternion MakeRotationEuler(const float x, const float y, const float z);
		static Quaternion MakeRotationEuler(const Vector3f& eulers);
		static Quaternion MakeRotationAngleAxis(const float angle, const Vector3f& axis);

		static Quaternion Lerp(const Quaternion& a, const Quaternion& b, const float t);
		static Quaternion Slerp(const Quaternion& a, const Quaternion& b, const float t);

		void operator+=(const Quaternion& q);
		void operator-=(const Quaternion& q);
		void operator*=(const Quaternion& q);
		void operator*=(const float& scalar);

		bool operator==(const Quaternion& other);
		bool operator!=(const Quaternion& other);
	};

	Quaternion operator+(const Quaternion& qA, const Quaternion& qB);
	Quaternion operator-(const Quaternion& qA, const Quaternion& qB);
	Quaternion operator*(const Quaternion& qA, const Quaternion& qB);

	Vector3f operator*(const Quaternion& q, const Vector3f& p);
}

#pragma warning(default : 4201)

