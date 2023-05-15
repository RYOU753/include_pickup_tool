#pragma once
#include <cmath>
#include <numbers>
#include "../Vector2.h"

namespace Kirara::Math
{
	template<typename T>
	constexpr T Vector2Template<T>::Magnitude(void) const
	{
		return static_cast<T>(hypot(x, y));
	}

	template<typename T>
	constexpr T Vector2Template<T>::SqMagnitude(void) const
	{
		return x * x + y * y;
	}

	template<typename T>
	constexpr T Vector2Template<T>::Distance(const Vector2Template& vec) const
	{
		return (*this - vec).Magnitude();
	}

	template<typename T>
	void Vector2Template<T>::Normalize(void)
	{
		T mag = Magnitude();
		x /= mag;
		y /= mag;
	}

	template<typename T>
	constexpr Vector2Template<T> Vector2Template<T>::Normalized(void)const
	{
		T mag = Magnitude();
		return Vector2Template<T>(x / mag, y / mag);
	}

	template<typename T>
	constexpr Vector2Template<T> Vector2Template<T>::RotateByRad(double rad)const
	{
		return Vector2Template<T>(static_cast<T>(x * cos(rad) - y * sin(rad)), static_cast<T>(x * sin(rad) + y * cos(rad)));
	}

	template<typename T>
	constexpr Vector2Template<T> Vector2Template<T>::RotateByDeg(double deg)const
	{
		constexpr double toRadAngle = std::numbers::pi / 180.0;
		return RotateByRad(toRadAngle * deg);
	}

	template<typename T>
	constexpr T Vector2Template<T>::Dot(const Vector2Template& vec)const
	{
		return x * vec.x + y * vec.y;
	}

	template<typename T>
	constexpr T Vector2Template<T>::Cross(const Vector2Template& vec)const
	{
		return x * vec.y - vec.x * y;
	}

	template<typename T>
	constexpr T Vector2Template<T>::Area(void) const
	{
		return x * y;
	}

	template<typename T>
	constexpr Vector2Template<T> Vector2Template<T>::Reflect(Vector2Template nVec) const
	{
		nVec.Normalize();
		return *this + 2 * (-Dot(nVec)) * nVec;
	}

	template<typename T>
	Vector2Template<T>& Vector2Template<T>::operator=(const Vector2Template& vec)
	{
		x = vec.x;
		y = vec.y;
		return *this;
	}

	template<typename T>
	T& Vector2Template<T>::operator[](int num)
	{
		return num % 2 ? y : x;
	}

	template<typename T>
	Vector2Template<T>& Vector2Template<T>::operator+=(const Vector2Template& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}

	template<typename T>
	Vector2Template<T>& Vector2Template<T>::operator+=(const T& num)
	{
		x += num;
		y += num;
		return *this;
	}

	template<typename T>
	Vector2Template<T>& Vector2Template<T>::operator-=(const Vector2Template& vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}

	template<typename T>
	Vector2Template<T>& Vector2Template<T>::operator*=(const Vector2Template<T>& vec)
	{
		x *= vec.x;
		y *= vec.y;
		return *this;
	}

	template<typename T>
	Vector2Template<T>& Vector2Template<T>::operator/=(const Vector2Template<T>& vec)
	{
		if (vec.x && vec.y)
		{
			x /= vec.x;
			y /= vec.y;
		}
		else if (!vec.x && !vec.y)
		{
			x = 0;
			y = 0;
		}
		else if (!vec.x)
		{
			x = 0;
			y /= vec.y;
		}
		else if (!vec.y)
		{
			x /= vec.x;
			y = 0;
		}

		return *this;
	}

	template<typename T>
	Vector2Template<T>& Vector2Template<T>::operator%=(const Vector2Template<T>& vec)
	{
		if (vec.x && vec.y)
		{
			x %= vec.x;
			y %= vec.y;
		}
		else if (!vec.x && !vec.y)
		{
			x = 0;
			y = 0;
		}
		else if (!vec.x)
		{
			x = 0;
			y %= vec.y;
		}
		else if (!vec.y)
		{
			x %= vec.x;
			y = 0;
		}

		return *this;
	}

	template<typename T>
	constexpr Vector2Template<T> Vector2Template<T>::operator+() const
	{
		return *this;
	}

	template<typename T>
	constexpr Vector2Template<T> Vector2Template<T>::operator-() const
	{
		return { -x,-y };
	}

	template<typename T>
	constexpr Vector2Template<T> Vector2Template<T>::operator+(Vector2Template vec)const
	{
		return Vector2Template{ x + vec.x, y + vec.y };
	}

	template<typename T>
	constexpr Vector2Template<T> Vector2Template<T>::operator-(Vector2Template vec)const
	{
		return Vector2Template{ x - vec.x, y - vec.y };
	}

	template<typename T>
	constexpr Vector2Template<T> Vector2Template<T>::operator*(Vector2Template vec)const
	{
		return Vector2Template{ x* vec.x, y* vec.y };
	}

	template<typename T>
	constexpr Vector2Template<T> Vector2Template<T>::operator/(Vector2Template vec)const
	{
		if (vec.x && vec.y)
		{
			return Vector2Template{ x / vec.x, y / vec.y };
		}
		else if (!vec.x && !vec.y)
		{
			return { 0,0 };
		}
		else if (!vec.x)
		{
			return { 0,y / vec.y };
		}
		else
		{
			return{ x / vec.x,0 };
		}

	}

	template<typename T>
	constexpr Vector2Template<T> Vector2Template<T>::operator%(Vector2Template vec)const
	{
		if (vec.x && vec.y)
		{
			return Vector2Template{ x% vec.x, y% vec.y };
		}
		else if (!vec.x && !vec.y)
		{
			return { 0,0 };
		}
		else if (!vec.x)
		{
			return { 0,y % vec.y };
		}
		else
		{
			return{ x % vec.x,0 };
		}
	}

	template<typename T>
	constexpr bool Vector2Template<T>::operator==(const Vector2Template& vec)const
	{
		return ((x == vec.x) && (y == vec.y));
	}

	template<typename T>
	constexpr bool Vector2Template<T>::operator!=(const Vector2Template& vec)const
	{
		return !((x == vec.x) && (y == vec.y));
	}

	template<typename T>
	constexpr bool Vector2Template<T>::operator<(const Vector2Template& vec)const
	{
		return ((x < vec.x) && (y < vec.y));
	}

	template<typename T>
	constexpr bool Vector2Template<T>::operator<=(const Vector2Template& vec)const
	{
		return ((x <= vec.x) && (y <= vec.y));
	}

	template<typename T>
	constexpr bool Vector2Template<T>::operator>(const Vector2Template& vec)const
	{
		return ((x > vec.x) && (y > vec.y));
	}

	template<typename T>
	constexpr bool Vector2Template<T>::operator>=(const Vector2Template& vec)const
	{
		return ((x >= vec.x) && (y >= vec.y));
	}

	template<typename T>
	constexpr Vector2Template<T> operator+(const Vector2Template<T>& vec, T num)
	{
		return Vector2Template<T>(vec.x + num, vec.y + num);
	}

	template<typename T>
	constexpr Vector2Template<T> operator+(T num, const Vector2Template<T>& vec)
	{
		return Vector2Template<T>(vec.x + num, vec.y + num);
	}

	template<typename T>
	constexpr Vector2Template<T> operator-(const Vector2Template<T>& vec, T num)
	{
		return Vector2Template<T>(vec.x - num, vec.y - num);
	}

	template<typename T>
	constexpr Vector2Template<T> operator-(T num, const Vector2Template<T>& vec)
	{
		return Vector2Template<T>(vec.x - num, vec.y - num);
	}

	template<typename T>
	constexpr Vector2Template<T> operator*(const Vector2Template<T>& vec, T num)
	{
		return Vector2Template<T>{ vec.x* num, vec.y* num };
	}

	template<typename T>
	constexpr Vector2Template<T> operator*(T num, const Vector2Template<T>& vec)
	{
		return Vector2Template<T>{ vec.x* num, vec.y* num };
	}

	template<typename T>
	constexpr Vector2Template<T> operator/(const Vector2Template<T>& vec, T num)
	{
		return Vector2Template<T>{ vec.x / num, vec.y / num };
	}

	template<typename T>
	constexpr Vector2Template<T> operator%(const Vector2Template<T>& vec, T num)
	{
		return Vector2Template<T>{ vec.x% num, vec.y% num };
	}

	template<typename T>
	constexpr Vector2Template<T> RotateByDeg(const Vector2Template<T>& center, const Vector2Template<T>& pos, double deg)
	{
		Vector2Template<T> ret;
		auto dir = pos - center;
		const auto rad = deg * std::numbers::pi / 180;
		ret.x = dir.x * cos(rad) - dir.y * sin(rad);
		ret.y = dir.y * cos(rad) + dir.x * sin(rad);
		ret = ret + center;
		return ret;
	}

	template<typename T>
	constexpr Vector2Template<T> RotateByRad(const Vector2Template<T>& center, const Vector2Template<T>& pos, double rad)
	{
		Vector2Template<T> ret;
		auto dir = pos - center;
		ret.x = dir.x * cos(rad) - dir.y * sin(rad);
		ret.y = dir.y * cos(rad) + dir.x * sin(rad);
		ret = ret + center;
		return ret;
	}

}
