#pragma once

#pragma warning(disable : 4201)
namespace Libero
{
	namespace Internal
	{
		template <typename T, size_t N>
		struct VectorBase
		{
			union
			{
				struct { T x, y, z, w; };
				struct { T r, g, b, a; };
				T data[N];
			};

			template <typename... V>
			VectorBase(const V&... components);
		};

		template <typename T>
		struct VectorBase<T, 1>
		{
			union
			{
				struct { T x; };
				struct { T r; };
				T data[1];
			};
			VectorBase<T, 1>(const T _x = 0) : x{ _x } {}
		};

		template <typename T>
		struct VectorBase<T, 2>
		{
			union
			{
				struct { T x, y; };
				struct { T r, g; };
				T data[2];
			};

			VectorBase<T, 2>(const T _x = 0, const T _y = 0) : x{ _x }, y{_y} {}
		};

		template <typename T>
		struct VectorBase<T, 3>
		{
			union
			{
				struct { T x, y, z; };
				struct { T r, g, b; };
				T data[3];
			};

			VectorBase<T, 3>(const T _x = 0, const T _y = 0, const T _z = 0) : x{ _x }, y{ _y }, z{ _z } {}
		};

		template <typename T>
		struct VectorBase<T, 4>
		{
			union
			{
				struct { T x, y, z, w; };
				struct { T r, g, b, a; };
				T data[4];
			};

			VectorBase<T, 4>(const T& _x = 0, const T _y = 0, const T _z = 0, const T _w = 0) : x{ _x }, y{ _y }, z{ _z }, w{ _w } {}
		};
	}

	template <typename T, size_t N>
	struct Vector : public Internal::VectorBase<T, N>
	{
		// Constructors:
		Vector() = default;
		template <typename... V>
		Vector(const V&... components);
		Vector(const Vector& other) = default;
		Vector(Vector&& other) = default;
		Vector& operator=(const Vector& other) = default;
		Vector& operator=(Vector&& other) = default;

		// Accessing data:
		T& operator[](size_t i);
		const T& operator[](size_t i) const;
		T& Data(size_t i);
		const T& Data(size_t i) const;

		// Normalizing:
		Vector Normalized() const;
		void Normalize();
		static void Normalize(Vector& vec);
		static Vector Normalized(const Vector& vec);

		// Angle measurement:
		float AngleBetween(const Vector& other) const;
		static float AngleBetween(const Vector& a, const Vector& b);

		// Magnitude:
		float Magnitude() const;
		float SqrMagnitude() const;
		static float Magnitude(const Vector& other);
		static float SqrMagnitude(const Vector& other);

		// Scaling:
		void Scale(float mag);
		Vector Scaled(float mag) const;
		static void Scale(Vector& vec, float mag);
		static Vector Scaled(const Vector& vec, float mag);

		// Cross & dot:
		float Dot(const Vector& other) const;
		static float Dot(const Vector& a, const Vector& b);

		float Cross(const Vector<T, 2>& other) const;
		Vector<T, 3> Cross(const Vector<T, 3>& other) const;
		static float Cross(const Vector<T, 2>& a, const Vector<T, 2>& b);
		static Vector<T, 3> Cross(const Vector<T, 3>& a, const Vector<T, 3>& b);

		// Comparison
		bool operator==(const Vector& other) const;
		bool operator!=(const Vector& other) const;

		// Inverting:
		const Vector& Inverted() const;
		void Inverse();
		static void Inverse(Vector& vec);
		static Vector Inverted(const Vector& vec);
		const Vector& operator-() const;

		// Lerp:
		static Vector Lerp(const Vector& a, const Vector& b, const float t);

		// Arithmatics:
		Vector& operator+=(const Vector& other);
		Vector& operator-=(const Vector& other);
		Vector& operator*=(const Vector& other);
		Vector& operator*=(const float scalar);
		Vector& operator/=(const Vector& other);
	};

	template <typename T, size_t N>
	Vector<T, N> operator+(const Vector<T, N>& a, const Vector<T, N>& b);
	template <typename T, size_t N>
	Vector<T, N> operator-(const Vector<T, N>& a, const Vector<T, N>& b);
	template <typename T, size_t N>
	Vector<T, N> operator*(const Vector<T, N>& a, const Vector<T, N>& b);
	template <typename T, size_t N>
	Vector<T, N> operator/(const Vector<T, N>& a, const Vector<T, N>& b);

	template <typename T, size_t N>
	Vector<T, N> operator*(const Vector<T, N>& a, const float b);
	template <typename T, size_t N>
	Vector<T, N> operator/(const Vector<T, N>& a, const float b);
	template <typename T, size_t N>
	Vector<T, N> operator*(const float a, const Vector<T, N>& b);

#pragma region Alias
	using Vector2f = Vector<float, 2>;
	using Vector2d = Vector<double, 2>;
	using Vector2i = Vector<int, 2>;

	using Point2f = Vector<float, 2>;
	using Point2d = Vector<double, 2>;
	using Point2i = Vector<int, 2>;

	using Vector3f = Vector<float, 3>;
	using Vector3d = Vector<double, 3>;
	using Vector3i = Vector<int, 3>;

	using Point3f = Vector<float, 3>;
	using Point3d = Vector<double, 3>;
	using Point3i = Vector<int, 3>;

	using Vector4f = Vector<float, 4>;
	using Vector4d = Vector<double, 4>;
	using Vector4i = Vector<int, 4>;

	using Point4f = Vector<float, 4>;
	using Point4d = Vector<double, 4>;
	using Point4i = Vector<int, 4>;

	using ColorRGBA = Vector<float, 4>;
	using ColorRGB = Vector<float, 3>;
	using Color = ColorRGB;
#pragma endregion
}
#include "Vector.inl"

#pragma warning(default : 4201)