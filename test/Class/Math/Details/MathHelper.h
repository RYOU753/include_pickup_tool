#pragma once
#include "../MathHelper.h"

namespace Kirara::Math
{
	template <ArithmeticType T>
	constexpr T RadToDeg(const T& rad)
	{
		return rad * static_cast<T>(180) / std::numbers::pi_v<T>;
	}

	template <ArithmeticType T>
	constexpr T DegToRad(const T& deg)
	{
		return deg * std::numbers::pi_v<T> / static_cast<T>(180);
	}

	template <ArithmeticType T>
	constexpr T RadIn2Pi(T rad)
	{
		constexpr auto pi2 = std::numbers::pi_v<T> * 2;
		rad = fmod(rad, pi2);
		return rad < 0 ? rad + pi2 : rad;
	}

	/// @brief 二つのベクトルの角度(角度が小さいほう)を求める
	/// @param from 基準
	/// @param to 図りたい角度のベクトル
	/// @return 角度(deg)(角度が小さいほう)
	template <ArithmeticType T>
	constexpr T AngleDeg(const Vector3Template<T>& from, const Vector3Template<T>& to)
	{
		const auto fLen = from.SqMagnitude();
		const auto tLen = to.SqMagnitude();
		const auto denominator = static_cast<float>(sqrt(fLen * tLen));
		if (denominator < K_EPSILON_NORMAL_SQRT)
		{
			return 0.0;
		}


		auto dot = static_cast<float>(from.Dot(to)) / denominator;
		if (dot < -1.0f)
		{
			dot = -1.0f;
		}
		if (dot > 1.0f)
		{
			dot = 1.0f;
		}

		const auto cross = from.Cross(to);
		const auto bit = cross.y < static_cast<T>(0)? -1.0f : 1.0f;

		auto d = RadToDeg(acos(dot)) * bit;
		
		float i = 0.0f;
		modf(d, &i);
		return i;
	}

	template<typename T>
	requires std::is_floating_point_v<T>
	constexpr bool FloatEqual(const T& val1, const T& val2)
	{
		return std::abs(val1 - val2) <= std::numeric_limits<T>::epsilon();
	}
}
