#include "Liber_pch.h"
#include "Quaternion.h"

namespace Libero
{
	Quaternion::Quaternion() : data{0, 0, 0, 0}{}
	Quaternion::Quaternion(float s, const Vector3f& v) : data{s, v.x, v.y, v.z}{}

	float Quaternion::Norm() const
	{
		return Norm(*this);
	}
	float Quaternion::Magnitude() const
	{
		return Norm();
	}
	float Quaternion::Norm(const Quaternion& qA)
	{
		return sqrt(qA.s * qA.s + qA.i * qA.i + qA.j * qA.j + qA.k * qA.k);
	}
	float Quaternion::Magnitude(const Quaternion& q)
	{
		return Norm(q);
	}

	Quaternion Quaternion::Normalized() const
	{
		return Normalized(*this);
	}
	void Quaternion::Normalize()
	{
		Normalize(*this);
	}
	Quaternion Quaternion::Normalized(const Quaternion& q)
	{
		float norm = Norm(q);
		if (norm == 0.0f) return q;

		float normVal = 1.0f / norm;
		return { q.s * normVal, q.v * normVal };
	}
	void Quaternion::Normalize(Quaternion& q)
	{
		q = Normalized(q);
	}

	void Quaternion::ToUnitNorm(){ ToUnitNorm(*this); }
	Quaternion Quaternion::UnitNorm() const
	{
		Quaternion cpy = *this;
		ToUnitNorm(cpy);
		return cpy;
	}
	void Quaternion::ToUnitNorm(Quaternion& q)
	{
		float angle = XMConvertToRadians(q.s);
		Vec::Normalize(q.v);
		q.s = cosf(angle * 0.5f);
		q.v = q.v * sinf(angle * 0.5f);
	}
	Quaternion Quaternion::UnitNorm(const Quaternion& q)
	{
		Quaternion cpy = q;
		ToUnitNorm(cpy);
		return cpy;
	}

	Quaternion Quaternion::Conjugate() const{ return Conjugate(*this); }
	Quaternion Quaternion::Conjugate(const Quaternion& q)
	{
		float s = q.s;
		Vector3f invAxis = q.v * -1;
		return { s, invAxis };
	}

	Quaternion Quaternion::Inverted() const{ return Inverted(*this); }
	void Quaternion::Inverse() { Inverse(*this); }
	Quaternion Quaternion::Inverted(const Quaternion& q)
	{
		float abs = q.Norm();
		abs *= abs;
		abs = 1.0f / abs;

		Quaternion conj = q.Conjugate();
		float scalar = conj.s * abs;
		Vector3f axis = conj.v * abs;
		return { scalar, axis };
	}
	void Quaternion::Inverse(Quaternion& q) { q = Inverted(q); }

	Vector3f Quaternion::RotateVectorAxis(float angle, const Vector3f& _v, const Vector3f& axis) const
	{
		// Vector to pure quat:
		Quaternion p{ 0, _v };

		// Normalize axis:
		Vector3f normAxis = Vec::Normalized(axis);

		// Create real quaternion:
		Quaternion q{ angle, normAxis };

		// Convert to unitNorm:
		ToUnitNorm(q);

		// invert quaternion
		Quaternion qInv = q.Inverted();

		// Rotate the point:
		return (q * p * qInv).v;
	}

	void Quaternion::operator+=(const Quaternion& q){ *this = *this + q; }
	void Quaternion::operator-=(const Quaternion& q){ *this = *this - q; }
	void Quaternion::operator*=(const Quaternion& q) { *this = *this * q; }
	void Quaternion::operator*=(const float& scalar) { s *= scalar; v *= scalar; }
	Quaternion operator+(const Quaternion& qA, const Quaternion& qB){ return { qA.s + qB.s, qA.v + qB.v }; }
	Quaternion operator-(const Quaternion& qA, const Quaternion& qB){ return { qA.s - qB.s, qA.v - qB.v }; }
	Quaternion operator*(const Quaternion& qA, const Quaternion& qB)
	{
		float scalar = qA.s * qB.s - Dot(qA.v, qB.v);
		Vector3f axis = qB.v * qA.s + qA.v * qB.s + Cross(qA.v, qB.v);
		return { scalar, axis };
	}
}

