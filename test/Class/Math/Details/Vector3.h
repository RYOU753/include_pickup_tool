#pragma once
#include <cmath>
#include "../Vector3.h"
//#include "../MathHelper.h"

namespace Kirara::Math
{
	template<class T>
	constexpr T Vector3Template<T>::Magnitude(void) const
	{
		return static_cast<T>(sqrt(SqMagnitude()));
	}

	template<class T>
	constexpr T Vector3Template<T>::SqMagnitude(void) const
	{
		return x * x + y * y + z * z;
	}

	template <class T>
	constexpr T Vector3Template<T>::Distance(const Vector3Template& vec) const
	{
		return (*this - vec).Magnitude();
	}

	template<class T>
	void Vector3Template<T>::Normalize(void)
	{
		T mag = Magnitude();
		x /= mag;
		y /= mag;
		z /= mag;
	}

	template<class T>
	constexpr Vector3Template<T> Vector3Template<T>::Normalized(void)const
	{
		T mag = Magnitude();
		return Vector3Template(x / mag, y / mag, z / mag);
	}

	template<class T>
	constexpr T Vector3Template<T>::Dot(const Vector3Template& vec)const
	{
		return x * vec.x + y * vec.y + z * vec.z;
	}

	template<class T>
	constexpr Vector3Template<T> Vector3Template<T>::Cross(const Vector3Template& vec)const
	{
		return Vector3Template(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
	}

	template<class T>
	constexpr T Vector3Template<T>::Area(void) const
	{
		return x * y * z;
	}

	template <class T>
	constexpr Vector3Template<T> Vector3Template<T>::Reflect(const Vector3Template& nVec) const
	{
		auto n = nVec.Normalized();
		return *this + 2 * (-Dot(n)) * n;
	}

	template<class T>
	Vector3Template<T>& Vector3Template<T>::operator=(const Vector3Template& vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
		return *this;
	}

	template<class T>
	T& Vector3Template<T>::operator[](int num)
	{
		switch (num % 3)
		{
		case 0:
			return x;

		case 1:
			return y;

		case 2:
			return z;

		default:
			return x;
		}
	}

	template<class T>
	Vector3Template<T>& Vector3Template<T>::operator+=(const Vector3Template& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}

	template<class T>
	Vector3Template<T>& Vector3Template<T>::operator+=(const T& num)
	{
		x += num;
		y += num;
		z += num;
		return *this;
	}

	template<class T>
	Vector3Template<T>& Vector3Template<T>::operator-=(const Vector3Template& vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}

	template<class T>
	Vector3Template<T>& Vector3Template<T>::operator*=(const Vector3Template& vec)
	{
		x *= vec.x;
		y *= vec.y;
		z *= vec.z;
		return *this;
	}

	template<class T>
	Vector3Template<T>& Vector3Template<T>::operator/=(const Vector3Template& vec)
	{
		if (vec.x)
		{
			x /= vec.x;
		}

		if (vec.y)
		{
			y /= vec.y;
		}

		if (vec.z)
		{
			z /= vec.z;
		}

		return *this;
	}

	template<class T>
	Vector3Template<T>& Vector3Template<T>::operator%=(const Vector3Template& vec)
	{
			if(vec.x)
			{
				x %= vec.x;
			}

			if(vec.y)
			{
				y %= vec.y;
			}

			if(vec.z)
			{
				z %= vec.z;
			}
		return *this;
	}

	template<>
	inline Vector3Template<float>& Vector3Template<float>::operator%=(const Vector3Template& vec)
	{
		if(vec.x!=static_cast<float>(0))
		{
			x = fmod(x, vec.x);
		}

		if(vec.y != static_cast<float>(0))
		{
			y = fmod(y, vec.y);
		}

		if(vec.z != static_cast<float>(0))
		{
			z = fmod(z, vec.z);
		}

		return *this;
	}
	template<>
	inline Vector3Template<double>& Vector3Template<double>::operator%=(const Vector3Template& vec)
	{
		if(vec.x != static_cast<double>(0))
		{
			x = fmod(x, vec.x);
		}

		if(vec.y != static_cast<double>(0))
		{
			y = fmod(y, vec.y);
		}

		if(vec.z != static_cast<double>(0))
		{
			z = fmod(z, vec.z);
		}

		return *this;
	}

	template<class T>
	constexpr Vector3Template<T> Vector3Template<T>::operator+() const
	{
		return *this;
	}

	template<class T>
	constexpr Vector3Template<T> Vector3Template<T>::operator-() const
	{
		return { -x,-y ,-z };
	}

	template<class T>
	constexpr Vector3Template<T> Vector3Template<T>::operator+(const Vector3Template& vec)const
	{
		return Vector3Template{ x + vec.x, y + vec.y, z + vec.z };
	}

	template<class T>
	constexpr Vector3Template<T> Vector3Template<T>::operator-(const Vector3Template& vec)const
	{
		return Vector3Template{ x - vec.x, y - vec.y, z - vec.z};
	}

	template<class T>
	constexpr Vector3Template<T> Vector3Template<T>::operator*(const Vector3Template& vec)const
	{
		return Vector3Template{ x* vec.x, y* vec.y, z* vec.z };
	}

	template<class T>
	constexpr Vector3Template<T> Vector3Template<T>::operator/(const Vector3Template& vec)const
	{
		Vector3Template ret = *this;
		ret /= vec;
		return ret;
	}

	template<class T>
	constexpr Vector3Template<T> Vector3Template<T>::operator%(const Vector3Template& vec)const
	{
		Vector3Template ret = *this;
		ret %= vec;
		return ret;
	}

	template<class T>
	constexpr bool Vector3Template<T>::operator==(const Vector3Template& vec)const
	{
		if constexpr(std::is_floating_point_v<T>)
		{
			return ((std::abs(x - vec.x) <= std::numeric_limits<T>::epsilon()) && (std::abs(y - vec.y) <= std::numeric_limits<T>::epsilon())) && (std::abs(y - vec.y) <= std::numeric_limits<T>::epsilon());
		}
		return ((x == vec.x) && (y == vec.y)) && (z == vec.z);
	}
	
	
	template<class T>
	constexpr bool Vector3Template<T>::operator!=(const Vector3Template& vec)const
	{
		return !operator==(vec);
	}

	template<class T>
	constexpr bool Vector3Template<T>::operator<(const Vector3Template& vec)const
	{
		return ((x < vec.x) && (y < vec.y) && (z < vec.z));
	}

	template<class T>
	constexpr bool Vector3Template<T>::operator<=(const Vector3Template& vec)const
	{
		return ((x <= vec.x) && (y <= vec.y) && (z <= vec.z));
	}

	template<class T>
	constexpr bool Vector3Template<T>::operator>(const Vector3Template& vec)const
	{
		return ((x > vec.x) && (y > vec.y) && (z > vec.z));
	}

	template<class T>
	constexpr bool Vector3Template<T>::operator>=(const Vector3Template& vec)const
	{
		return ((x >= vec.x) && (y >= vec.y) && (z >= vec.z));
	}

	template<class T>
	template<class Vec>
	Vector3Template<T>& Vector3Template<T>::operator()(const Vec& vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;

		return *this;
	}

	template<class T>
	constexpr Vector3Template<T> operator+(const Vector3Template<T>& vec, const T& num)
	{
		return Vector3Template<T>(vec.x + num, vec.y + num, vec.z + num);
	}

	template<class T>
	constexpr Vector3Template<T> operator+(const T& num, const Vector3Template<T>& vec)
	{
		return Vector3Template<T>(vec.x + num, vec.y + num, vec.z + num);
	}

	template<class T>
	constexpr Vector3Template<T> operator-(const Vector3Template<T>& vec, const T& num)
	{
		return Vector3Template<T>(vec.x - num, vec.y - num, vec.z - num);
	}

	template<class T>
	constexpr Vector3Template<T> operator-(const T& num, const Vector3Template<T>& vec)
	{
		return Vector3Template<T>(vec.x - num, vec.y - num, vec.z - num);
	}

	template<class T>
	constexpr Vector3Template<T> operator*(const Vector3Template<T>& vec, const T& num)
	{
		return Vector3Template<T>{ vec.x* num, vec.y* num, vec.z* num };
	}

	template<class T>
	constexpr Vector3Template<T> operator*(const T& num, const Vector3Template<T>& vec)
	{
		return Vector3Template<T>{ vec.x* num, vec.y* num, vec.z* num };
	}

	template<class T>
	constexpr Vector3Template<T> operator/(const Vector3Template<T>& vec, const T& num)
	{
		return Vector3Template<T>{ vec.x / num, vec.y / num, vec.z / num};
	}

	template<class T>
	constexpr Vector3Template<T> operator%(const Vector3Template<T>& vec, const T& num)
	{
		if constexpr (std::is_floating_point_v<T>)
		{
			return Vector3Template<T>{fmod(vec.x, num), fmod(vec.y, num), fmod(vec.z, num)};
		}
		return Vector3Template<T>{ vec.x% num, vec.y% num, vec.z% num};
	}

}
