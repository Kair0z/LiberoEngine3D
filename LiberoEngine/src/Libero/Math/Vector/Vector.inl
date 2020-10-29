#include "Vector.h"
#include <utility>
#include <memory>
#include <cmath>
#include <cassert>

namespace Libero
{
	template<typename T, size_t N>
	template<typename ...V>
	inline Vector<T, N>::Vector(const V& ...components) : Internal::VectorBase<T, N>((T)components...) {}

#pragma region Data Access
	template<typename T, size_t N>
	inline T& Vector<T, N>::operator[](size_t i)
	{
		assert(i < N);
		return this->data[i];
	}
	template<typename T, size_t N>
	inline const T& Vector<T, N>::operator[](size_t i) const
	{
		assert(i < N);
		return this->data[i];
	}
	template<typename T, size_t N>
	inline T& Vector<T, N>::Data(size_t i)
	{
		assert(i < N);
		return *this[i];
	}
	template<typename T, size_t N>
	inline const T& Vector<T, N>::Data(size_t i) const
	{
		assert(i < N);
		return *this[i];
	}
#pragma endregion

#pragma region Normalizing
	template<typename T, size_t N>
	inline Vector<T, N> Vector<T, N>::Normalized() const
	{
		return Vector<T,N>::Normalized(*this);
	}
	template<typename T, size_t N>
	inline void Vector<T, N>::Normalize() { Normalize(*this); }
	template<typename T, size_t N>
	inline void Vector<T, N>::Normalize(Vector& vec) { vec = Normalized(vec); }
	template<typename T, size_t N>
	inline Vector<T, N> Vector<T, N>::Normalized(const Vector<T, N>& vec)
	{
		return vec / vec.Magnitude();
	}
#pragma endregion

#pragma region Angle
	template<typename T, size_t N>
	inline float Vector<T, N>::AngleBetween(const Vector& other) const
	{
		return AngleBetween(*this, other);
	}
	template <typename T, size_t N>
	inline float Vector<T, N>::AngleBetween(const Vector<T, N>& a, const Vector<T, N>& b)
	{
		float magA = Magnitude(a);
		float magB = Magnitude(b);
		if (magA == 0.0f || magB == 0.0f) return 0.0f;

		return std::acosf(Dot(a, b) / (magA * magB));
	}
#pragma endregion

#pragma region Magnitude
	template<typename T, size_t N>
	inline float Vector<T, N>::Magnitude() const
	{
		return Magnitude(*this);
	}
	template<typename T, size_t N>
	inline float Vector<T, N>::SqrMagnitude() const
	{
		return SqrMagnitude(*this);
	}
	template<typename T, size_t N>
	inline float Vector<T, N>::Magnitude(const Vector& other)
	{
		return sqrtf(SqrMagnitude(other));
	}

	template<typename T, size_t N>
	inline float Vector<T, N>::SqrMagnitude(const Vector& other)
	{
		return Dot(other, other);
	}
#pragma endregion

#pragma region Scaling
	template<typename T, size_t N>
	inline void Vector<T, N>::Scale(float mag)
	{
		Scale(*this, mag);
	}
	template<typename T, size_t N>
	inline Vector<T, N> Vector<T, N>::Scaled(float mag) const
	{
		return Scaled(*this, mag);
	}
	template<typename T, size_t N>
	inline void Vector<T, N>::Scale(Vector& vec, float mag)
	{
		vec = vec.Normalized() * mag;
	}
	template<typename T, size_t N>
	inline Vector<T, N> Vector<T, N>::Scaled(const Vector& vec, float mag)
	{
		Vector<T, N> res = vec;
		Scale(res, mag);
		return res;
	}
#pragma endregion

#pragma region Dot & Cross
	template<typename T, size_t N>
	inline float Vector<T, N>::Dot(const Vector& other) const
	{
		return Dot(*this, other);
	}
	template<typename T, size_t N>
	inline float Vector<T, N>::Dot(const Vector& a, const Vector& b)
	{
		float result{};
		for (size_t i{}; i < N; ++i) result += a[i] * b[i];
		return result;
	}

	template<typename T, size_t N>
	inline float Vector<T, N>::Cross(const Vector<T, 2>& other) const
	{
		return Cross(*this, other);
	}
	template<typename T, size_t N>
	inline Vector<T, 3> Vector<T, N>::Cross(const Vector<T, 3>& other) const
	{
		return Cross(*this, other);
	}
	template<typename T, size_t N> // 2D
	inline float Vector<T, N>::Cross(const Vector<T, 2>& a, const Vector<T, 2>& b)
	{
		return { a.x * b.y - a.y * b.x };
	}
	template<typename T, size_t N> // 3D
	inline Vector<T, 3> Vector<T, N>::Cross(const Vector<T, 3>& a, const Vector<T, 3>& b)
	{
		return
		{
			a[1] * b[2] - a[2] * b[1],
			a[2] * b[0] - a[0] * b[2],
			a[0] * b[1] - a[1] * b[0]
		};
	}
#pragma endregion

#pragma region Inversion
	template<typename T, size_t N>
	inline const Vector<T, N>& Vector<T, N>::Inverted() const
	{
		return Inverted(*this);
	}
	template<typename T, size_t N>
	inline void Vector<T, N>::Inverse()
	{
		Inverse(*this);
	}
	template<typename T, size_t N>
	inline void Vector<T, N>::Inverse(Vector& vec)
	{
		vec = Inverted(vec);
	}
	template<typename T, size_t N>
	inline Vector<T, N> Vector<T, N>::Inverted(const Vector& vec)
	{
		Vector<T, N> res = vec;
		for (size_t i{}; i < N; ++i) res[i] = -res[i];

		return res;
	}
	template<typename T, size_t N>
	inline const Vector<T, N>& Vector<T, N>::operator-() const
	{
		Inverse(*this);
		return *this;
	}
#pragma endregion

#pragma region Lerp
	template<typename T, size_t N>
	inline Vector<T, N> Vector<T, N>::Lerp(const Vector& a, const Vector& b, const float t)
	{
		return a * t + b * (1.0f - t);
	}
#pragma endregion

#pragma region Comparison
	template<typename T, size_t N>
	inline bool Vector<T, N>::operator==(const Vector& other) const
	{
		bool same = true;
		for (size_t i{}; i < N; ++i) same = same && (Data(i) == other->Data(i));

		return same;
	}
	template<typename T, size_t N>
	inline bool Vector<T, N>::operator!=(const Vector& other) const
	{
		return !(*this == other);
	}
#pragma endregion

#pragma region Arithmetic
	template<typename T, size_t N>
	inline Vector<T, N>& Vector<T, N>::operator+=(const Vector& other)
	{
		*this = *this + other;
	}
	template<typename T, size_t N>
	inline Vector<T, N>& Vector<T, N>::operator-=(const Vector& other)
	{
		*this = *this - other;
	}
	template<typename T, size_t N>
	inline Vector<T, N>& Vector<T, N>::operator*=(const Vector& other)
	{
		*this = *this * other;
	}
	template<typename T, size_t N>
	inline Vector<T, N>& Vector<T, N>::operator*=(const float scalar)
	{
		return *this = *this * scalar;
	}
	template<typename T, size_t N>
	inline Vector<T, N>& Vector<T, N>::operator/=(const Vector& other)
	{
		*this = *this / other;
	}
	template<typename T, size_t N>
	Vector<T, N> operator+(const Vector<T, N>& a, const Vector<T, N>& b)
	{
		Vector<T, N> res{};
		for (size_t i{}; i < N; ++i)
			res[i] = a[i] + b[i];

		return res;
	}
	template<typename T, size_t N>
	Vector<T, N> operator-(const Vector<T, N>& a, const Vector<T, N>& b)
	{
		Vector<T, N> res{};
		for (size_t i{}; i < N; ++i)
			res[i] = a[i] - b[i];

		return res;
	}
	template<typename T, size_t N>
	Vector<T, N> operator*(const Vector<T, N>& a, const Vector<T, N>& b)
	{
		Vector<T, N> res{};
		for (size_t i{}; i < N; ++i)
			res[i] = a[i] * b[i];

		return res;
	}
	template<typename T, size_t N>
	Vector<T, N> operator/(const Vector<T, N>& a, const Vector<T, N>& b)
	{
		Vector<T, N> res{};
		for (size_t i{}; i < N; ++i)
			res[i] = a[i] / b[i];

		return res;
	}
	template<typename T, size_t N>
	Vector<T, N> operator*(const Vector<T, N>& a, const float b)
	{
		Vector<T, N> res{};
		for (size_t i{}; i < N; ++i)
			res[i] = a[i] * b;

		return res;
	}
	template<typename T, size_t N>
	Vector<T, N> operator/(const Vector<T, N>& a, const float b)
	{
		Vector<T, N> res{};
		for (size_t i{}; i < N; ++i)
			res[i] = a[i] / b;

		return res;
	}
	template<typename T, size_t N>
	Vector<T, N> operator*(const float a, const Vector<T, N>& b)
	{
		Vector<T, N> res{};
		for (size_t i{}; i < N; ++i)
			res[i] = a * b[i];

		return res;
	}
#pragma endregion
}