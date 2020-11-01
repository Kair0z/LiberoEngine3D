#include "Matrix.h"

namespace Libero
{
	namespace Math
	{
		template<typename T, size_t C, size_t R>
		inline void Matrix<T, C, R>::OnEachElement(std::function<void(T&)> operation)
		{
			for (size_t r{}; r < R; ++r)
				for (size_t c{}; c < C; ++c)
				{
					size_t i = c + (R * r);
					operation(this->data[i]);
				}
		}

		template<typename T, size_t C, size_t R>
		inline Matrix<T, C, R> Matrix<T, C, R>::Identity()
		{
			Matrix<T, C, R> result{};
			for (size_t r{}; r < R; ++r)
				for (size_t c{}; c < C; ++c)
				{
					size_t i = c + (R * r);
					if (r == c) result.data[i] = (T)1;
				}

			return result;
		}

		template<typename T, size_t C, size_t R>
		inline Matrix<T, C, R>& Matrix<T, C, R>::operator-()
		{
			OnEachElement([](T& element)
				{
					element = -element;
				});

			return *this;
		}

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
	}
}