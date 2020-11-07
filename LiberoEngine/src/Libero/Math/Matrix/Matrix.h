#pragma once
#include <array>
#include <functional>
#include <utility>
#pragma warning(disable : 4201)
namespace Libero
{
	namespace Math
	{
		namespace Internal
		{
			template <typename T, size_t C, size_t R>
			struct MatrixBase
			{
				size_t colSize{C};
				size_t rowSize{R};
				T data[C * R];

				template <class... Init>
				MatrixBase(Init...values) : data{(T)values...}{}
			};
		}

		template <typename T, size_t C, size_t R>
		struct Matrix : public Internal::MatrixBase<T, C, R>
		{
		public:
			Matrix() = default;
			template <class... Init>
			Matrix(Init... values) : Internal::MatrixBase<T, C, R>(values...) {}
			Matrix(const Matrix& other) = default;
			Matrix(Matrix&& other) = default;
			Matrix& operator=(const Matrix& other) = default;
			Matrix& operator=(Matrix&& other) = default;
			template <typename OtherT>
			Matrix(const Matrix<OtherT, C, R>& other);
			template <typename OtherT>
			Matrix(Matrix<OtherT, C, R>&& other);
			
			// Data Access:
			const T* operator[](size_t r) const;
			T* operator[](size_t r);
			T& Element(size_t c, size_t r);
			const T& Element(size_t c, size_t r) const;
			T& Element(size_t idx);
			const T& Element(size_t idx) const;

			// Basic Operations:
			Matrix& operator-();
			Matrix& operator*=(const float scalar);
			Matrix& operator/=(const float scalar);
			Matrix& operator+=(const Matrix& other);
			Matrix& operator-=(const Matrix& other);

			// Transpose:
			Matrix& Transpose();
			Matrix Transposed() const;
			static void Transpose(Matrix& matrix);
			static Matrix Transposed(const Matrix& matrix);

			// Summation:
			T Sum() const;
			static T Sum(const Matrix& matrix);

			// IsNull:
			bool IsNull() const;
			static bool IsNull(const Matrix& matrix);


			static Matrix Identity();

			void OnEachElement(std::function<void(T&)> operation);
			void OnEachElement(std::function<void(T&, size_t idx)> operation);
			void OnEachElement(std::function<void(const T&)> operation) const;
			void OnEachElement(std::function<void(const T&, size_t idx)> operation) const;
		};

		// Matrix - Matrix
		template <typename T, size_t C, size_t R>
		Matrix<T, C, R> operator+(const Matrix<T, C, R>& a, const Matrix<T, C, R>& b);
		template <typename T, size_t C, size_t R>
		Matrix<T, C, R> operator-(const Matrix<T, C, R>& a, const Matrix<T, C, R>& b);
		template <typename T, size_t C, size_t R>
		Matrix<T, C, R> operator*(const Matrix<T, C, R>& a, const Matrix<T, C, R>& b);
		template <typename T, size_t C, size_t R>
		Matrix<T, C, R> operator/(const Matrix<T, C, R>& a, const Matrix<T, C, R>& b);

		// Matrix - scalar
		template <typename T, size_t C, size_t R>
		Matrix<T, C, R> operator*(const Matrix<T, C, R>& a, float b);
		template <typename T, size_t C, size_t R>
		Matrix<T, C, R> operator/(const Matrix<T, C, R>& a, float b);
		template <typename T, size_t C, size_t R>
		Matrix<T, C, R> operator*(float a, const Matrix<T, C, R>& b);
		template <typename T, size_t C, size_t R>
		Matrix<T, C, R> operator/(float a, const Matrix<T, C, R>& b);

		// Aliases:
		using Matrix2x2f = Matrix<float, 2, 2>;
		using Matrix2x2d = Matrix<double, 2, 2>;
		using Matrix2x2i = Matrix<int, 2, 2>;
		using Matrix2x2ui = Matrix<uint32_t, 2, 2>;

		using Matrix3x3f = Matrix<float, 3, 3>;
		using Matrix3x3d = Matrix<double, 3, 3>;
		using Matrix3x3i = Matrix<int, 3, 3>;
		using Matrix3x3ui = Matrix<uint32_t, 3, 3>;

		using Matrix4x4f = Matrix<float, 4, 4>;
		using Matrix4x4d = Matrix<double, 4, 4>;
		using Matrix4x4i = Matrix<int, 4, 4>;
		using Matrix4x4ui = Matrix<uint32_t, 4, 4>;
	}
}
#include "Matrix.inl"
#pragma warning(default : 4201)


