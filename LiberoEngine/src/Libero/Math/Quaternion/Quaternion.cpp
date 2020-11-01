#include "Quaternion.h"
#include "../Vector/Vector.h"

namespace Libero
{
	namespace Math
	{
		Quaternion::Quaternion(float i, float j, float k, float s) : data{ i, j, k, s } {}
		Quaternion::Quaternion(const Vector3f& v, float s) : data{ v.x, v.y, v.z, s } {}
		Quaternion::Quaternion(float s, const Vector3f& v) : Quaternion(v, s) {};

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

		void Quaternion::ToUnitNorm() { ToUnitNorm(*this); }
		Quaternion Quaternion::UnitNorm() const
		{
			Quaternion cpy = *this;
			ToUnitNorm(cpy);
			return cpy;
		}
		void Quaternion::ToUnitNorm(Quaternion& q)
		{
			float angle = q.s;
			Vector3f::Normalize(q.v);
			q.s = cosf(angle * 0.5f);
			q.v = q.v * sinf(angle * 0.5f);
		}
		Quaternion Quaternion::UnitNorm(const Quaternion& q)
		{
			Quaternion cpy = q;
			ToUnitNorm(cpy);
			return cpy;
		}

		Quaternion Quaternion::Conjugate() const { return Conjugate(*this); }
		Quaternion Quaternion::Conjugate(const Quaternion& q)
		{
			float s = q.s;
			Vector3f invAxis = q.v * -1;
			return { s, invAxis };
		}

		Quaternion Quaternion::Inverted() const { return Inverted(*this); }
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

		Vector3f Quaternion::GetEulerAngles(bool round) const
		{
			// https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
			Vector3f angles{};

			// Roll (x):
			float sinr_cosp = 2 * (s * i + j * k);
			float cosr_cosp = 1 - 2 * (i * i + j * j);
			angles.x = std::atan2f(sinr_cosp, cosr_cosp);

			// Pitch (y):
			float sinp = 2 * (s * j - k * i);
			if (std::abs(sinp) >= 1) angles.y = std::copysign(Math::fPI / 2.0f, sinp);
			else angles.y = std::asinf(sinp);

			// Yaw (z):
			float siny_cosp = 2 * (s * k + i * j);
			float cosy_cosp = 1 - 2 * (j * j + k * k);
			angles.z = std::atan2f(siny_cosp, cosy_cosp);

			angles.x = Math::ToDegrees(angles.x);
			angles.y = Math::ToDegrees(angles.y);
			angles.z = Math::ToDegrees(angles.z);

			if (round)
			{
				angles.x = Math::Round(angles.x);
				angles.y = Math::Round(angles.y);
				angles.z = Math::Round(angles.z);
			}
			return angles;
		}
		Vector3f Quaternion::RotateVectorAxis(float angle, const Vector3f& _v, const Vector3f& axis) const
		{
			float a = Math::ToRadians(angle);

			// Vector to pure quat:
			Quaternion p{ 0, _v };

			// Create real quaternion:
			Quaternion q = MakeRotationAngleAxis(angle, axis);

			// invert quaternion
			Quaternion qInv = q.Inverted();

			// Rotate the point:
			return (q * p * qInv).v;
		}

		Quaternion Quaternion::MakeRotationFromTo(const Vector3f& from, const Vector3f& to, const Vector3f& up)
		{
			Vector3f forward = (to - from).Normalized();
			Vector3f right = up.Cross(forward);
			return Quaternion();
		}
		Quaternion Quaternion::MakeRotationEuler(const float x, const float y, const float z)
		{
			// https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
			float yaw = Math::ToRadians(z), roll = Math::ToRadians(x), pitch = Math::ToRadians(y);

			float cy = cosf(yaw * 0.5f);
			float sy = sinf(yaw * 0.5f);
			float cp = cosf(pitch * 0.5f);
			float sp = sinf(pitch * 0.5f);
			float cr = cosf(roll * 0.5f);
			float sr = sinf(roll * 0.5f);

			Quaternion q;
			q.s = cr * cp * cy + sr * sp * sy;
			q.i = sr * cp * cy - cr * sp * sy;
			q.j = cr * sp * cy + sr * cp * sy;
			q.k = cr * cp * sy - sr * sp * cy;

			return q.Normalized();
		}
		Quaternion Quaternion::MakeRotationEuler(const Vector3f& eulers)
		{
			return MakeRotationEuler(eulers.x, eulers.y, eulers.z);
		}
		Quaternion Quaternion::MakeRotationAngleAxis(const float angle, const Vector3f& axis)
		{
			Vector3f axNorm = axis.Normalized();
			Quaternion res{ Math::ToRadians(angle), axis };
			res.ToUnitNorm();
			return res;
		}

		Quaternion Quaternion::Lerp(const Quaternion& a, const Quaternion& b, const float t)
		{
			float t_ = 1 - t;
			Quaternion temp{ t_ * a.i + t * b.i, t_ * a.j + t * b.j, t_ * a.k + t * b.k, t_ * a.s + t * b.s };
			return temp.Normalized();
		}
		Quaternion Quaternion::Slerp(const Quaternion& a, const Quaternion& b, const float t)
		{
			float t_ = 1 - t;
			float theta = acosf(a.i * b.i + a.j * b.j + a.k * b.k + a.s * b.s);
			float sn = sin(theta);

			float Wa{ sin(t_ * theta) / sn };
			float Wb{ sin(t * theta) / sn };

			Quaternion temp{
				Wa * a.i + Wb * b.i,
				Wa * a.j + Wb * b.j,
				Wa * a.k + Wb * b.k,
				Wa * a.s + Wb * b.s };

			return temp.Normalized();
		}

		void Quaternion::operator+=(const Quaternion& q) { *this = *this + q; }
		void Quaternion::operator-=(const Quaternion& q) { *this = *this - q; }
		void Quaternion::operator*=(const Quaternion& q) { *this = *this * q; }
		void Quaternion::operator*=(const float& scalar) { s *= scalar; v *= scalar; }
		bool Quaternion::operator==(const Quaternion& other)
		{
			return (this->i == other.i && this->j == other.j && this->k == other.k && this->s == other.s);
		}
		bool Quaternion::operator!=(const Quaternion& other)
		{
			return !(*this == other);
		}

		Quaternion operator+(const Quaternion& qA, const Quaternion& qB) { return { qA.s + qB.s, qA.v + qB.v }; }
		Quaternion operator-(const Quaternion& qA, const Quaternion& qB) { return { qA.s - qB.s, qA.v - qB.v }; }
		Quaternion operator*(const Quaternion& qA, const Quaternion& qB)
		{
			float scalar = qA.s * qB.s - Vector3f::Dot(qA.v, qB.v);
			Vector3f axis = qB.v * qA.s + qA.v * qB.s + Vector3f::Cross(qA.v, qB.v);
			return { scalar, axis };
		}
		Vector3f operator*(const Quaternion& q, const Vector3f& p)
		{
			Quaternion quat = q;

			// Vector to pure quaternion:
			Quaternion qp{ 0, p };

			Quaternion qInv = quat.Inverted();

			return (quat * qp * qInv).v;
		}
	}
}

