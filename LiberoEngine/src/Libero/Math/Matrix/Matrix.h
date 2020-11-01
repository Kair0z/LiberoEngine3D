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

			static Matrix Identity();

		private:
			void OnEachElement(std::function<void(T&)> operation);
		};

		// Matrix - Matrix
		template <typename T, size_t C, size_t R>
		Matrix<T, C, R> operator+(const Matrix<T, C, R>& a, const Matrix<T, C, R>& b);
		template <typename T, size_t C, size_t R>
		Matrix<T, C, R> operator-(const Matrix<T, C, R>& a, const Matrix<T, C, R>& b);

		// Matrix - scalar
		template <typename T, size_t C, size_t R>
		Matrix<T, C, R> operator*(const Matrix<T, C, R>& a, float b);
		template <typename T, size_t C, size_t R>
		Matrix<T, C, R> operator/(const Matrix<T, C, R>& a, float b);
		template <typename T, size_t C, size_t R>
		Matrix<T, C, R> operator*(float a, const Matrix<T, C, R>& b);
		template <typename T, size_t C, size_t R>
		Matrix<T, C, R> operator/(float a, const Matrix<T, C, R>& b);
	}
}
#include "Matrix.inl"
#pragma warning(default : 4201)


