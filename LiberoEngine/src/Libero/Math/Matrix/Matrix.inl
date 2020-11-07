#include "Matrix.h"
#include <cassert>

namespace Libero
{
	namespace Math
	{
		template<typename T, size_t C, size_t R>
		inline T Matrix<T, C, R>::Sum() const
		{
			T sum{};
			OnEachElement([&sum](const T& element)
				{
					sum += element;
				});

			return sum;
		}
		template<typename T, size_t C, size_t R>
		inline T Matrix<T, C, R>::Sum(const Matrix& matrix)
		{
			return matrix.Sum();
		}
		template<typename T, size_t C, size_t R>
		inline bool Matrix<T, C, R>::IsNull() const
		{
			for (size_t r{}; r < R; ++r)
				for (size_t c{}; c < C; ++c)
				{
					if (Element(c, r) != (T)0) 
						return false;
				}

			return true;
		}
		template<typename T, size_t C, size_t R>
		inline bool Matrix<T, C, R>::IsNull(const Matrix& matrix)
		{
			return matrix.IsNull();
		}
		template<typename T, size_t C, size_t R>
		inline Matrix<T, C, R> Matrix<T, C, R>::Identity()
		{
			Matrix<T, C, R> result{};
			for (size_t r{}; r < R; ++r)
				for (size_t c{}; c < C; ++c)
				{
					size_t i = c + (C * r);
					if (r == c) result.data[i] = (T)1;
				}

			return result;
		}

		// Constructor:
		template<typename T, size_t C, size_t R>
		template <typename OtherT>
		Matrix<T, C, R>::Matrix(const Matrix<OtherT, C, R>& other)
		{
			OnEachElement([&other](T& element, size_t idx) { element = static_cast<T>(other.Element(idx)); });
		}
		template<typename T, size_t C, size_t R>
		template <typename OtherT>
		Matrix<T, C, R>::Matrix(Matrix<OtherT, C, R>&& other)
		{
			OnEachElement([&other](T& element, size_t idx) { element = static_cast<T>(other.Element(idx)); });
		}

		// Data Access:
		template<typename T, size_t C, size_t R>
		inline const T* Matrix<T, C, R>::operator[](size_t r) const
		{
			assert(r < R);
			return &this->data[C * r];
		}
		template<typename T, size_t C, size_t R>
		inline T* Matrix<T, C, R>::operator[](size_t r)
		{
			assert(r < R);
			return &this->data[C * r];
		}
		template<typename T, size_t C, size_t R>
		inline T& Matrix<T, C, R>::Element(size_t c, size_t r)
		{
			assert(r < R && c < C);
			return (*this)[r][c];
		}
		template<typename T, size_t C, size_t R>
		inline const T& Matrix<T, C, R>::Element(size_t c, size_t r) const
		{
			assert(r < R && c < C);
			return (*this)[r][c];
		}
		template<typename T, size_t C, size_t R>
		inline T& Matrix<T, C, R>::Element(size_t idx)
		{
			assert(idx < C * R);
			return Element(idx % C, idx / R);
		}
		template<typename T, size_t C, size_t R>
		inline const T& Matrix<T, C, R>::Element(size_t idx) const
		{
			assert(idx < C * R);
			return Element(idx % C, idx / R);
		}

		// Unary Operations:
		template<typename T, size_t C, size_t R>
		inline Matrix<T, C, R>& Matrix<T, C, R>::operator-()
		{
			OnEachElement([](T& element)
				{
					element = -element;
				});

			return *this;
		}
		template<typename T, size_t C, size_t R>
		inline Matrix<T, C, R>& Matrix<T, C, R>::operator*=(const float scalar)
		{
			OnEachElement([](T& element)
				{
					element *= scalar;
				});

			return *this;
		}
		template<typename T, size_t C, size_t R>
		inline Matrix<T, C, R>& Matrix<T, C, R>::operator/=(const float scalar)
		{
			OnEachElement([](T& element)
				{
					element /= scalar;
				});

			return *this;
		}


		// Operations: Matrix - Scalar
		template <typename T, size_t C, size_t R>
		inline Matrix<T, C, R> operator*(const Matrix<T, C, R>& a, float b)
		{
			Matrix<T, C, R> result = a;
			result.OnEachElement([](T& el) { el *= b; });
			return result;
		}
		template <typename T, size_t C, size_t R>
		inline Matrix<T, C, R> operator/(const Matrix<T, C, R>& a, float b)
		{
			Matrix<T, C, R> result = a;
			result.OnEachElement([](T& el) { el /= b; });
			return result;
		}
		template <typename T, size_t C, size_t R>
		Matrix<T, C, R> operator*(float a, const Matrix<T, C, R>& b)
		{
			Matrix<T, C, R> result = b;
			result.OnEachElement([](T& el) { el *= a; });
			return result;
		}
		template <typename T, size_t C, size_t R>
		Matrix<T, C, R> operator/(float a, const Matrix<T, C, R>& b)
		{
			Matrix<T, C, R> result = b;
			result.OnEachElement([](T& el) { el /= a; });
			return result;
		}


		// Operations: Matrix - Matrix
		template<typename T, size_t C, size_t R>
		Matrix<T, C, R> operator+(const Matrix<T, C, R>& a, const Matrix<T, C, R>& b)
		{
			Matrix<T, C, R> result = a;
			result.OnEachElement([=, &result](T& element, size_t idx)
				{
					result.Element(idx) += b.Element(idx);
				});

			return result;
		}
		template<typename T, size_t C, size_t R>
		Matrix<T, C, R> operator-(const Matrix<T, C, R>& a, const Matrix<T, C, R>& b)
		{
			Matrix<T, C, R> result = a;
			result.OnEachElement([=, &result](T& element, size_t idx)
				{
					result.Element(idx) -= b.Element(idx);
				});

			return result;
		}
		template<typename T, size_t C, size_t R>
		Matrix<T, C, R> operator*(const Matrix<T, C, R>& a, const Matrix<T, C, R>& b)
		{
			Matrix<T, C, R> result = a;
			result.OnEachElement([=, &result](T& element, size_t idx)
				{
					result.Element(idx) *= b.Element(idx);
				});

			return result;
		}
		template<typename T, size_t C, size_t R>
		Matrix<T, C, R> operator/(const Matrix<T, C, R>& a, const Matrix<T, C, R>& b)
		{
			Matrix<T, C, R> result = a;
			result.OnEachElement([=, &result](T& element, size_t idx)
				{
					result.Element(idx) /= b.Element(idx);
				});

			return result;
		}

		template<typename T, size_t C, size_t R>
		inline void Matrix<T, C, R>::OnEachElement(std::function<void(T&)> operation)
		{
			for (size_t r{}; r < R; ++r)
				for (size_t c{}; c < C; ++c)
				{
					size_t i = c + (C * r);
					operation(this->data[i]);
				}
		}
		template<typename T, size_t C, size_t R>
		inline void Matrix<T, C, R>::OnEachElement(std::function<void(T&, size_t idx)> operation)
		{
			for (size_t r{}; r < R; ++r)
				for (size_t c{}; c < C; ++c)
				{
					size_t i = c + (C * r);
					operation(this->data[i], i);
				}
		}
		template<typename T, size_t C, size_t R>
		inline void Matrix<T, C, R>::OnEachElement(std::function<void(const T&)> operation) const
		{
			for (size_t r{}; r < R; ++r)
				for (size_t c{}; c < C; ++c)
				{
					size_t i = c + (C * r);
					operation(this->data[i]);
				}
		}
		template<typename T, size_t C, size_t R>
		inline void Matrix<T, C, R>::OnEachElement(std::function<void(const T&, size_t idx)> operation) const
		{
			for (size_t r{}; r < R; ++r)
				for (size_t c{}; c < C; ++c)
				{
					size_t i = c + (C * r);
					operation(this->data[i], i);
				}
		}
	}
}