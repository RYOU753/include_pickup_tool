#pragma once
#include "MathDefinition.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Quaternion.h"

namespace Kirara::Math
{
	template<ArithmeticType T>
	constexpr T RadToDeg(const T& rad);

	template<ArithmeticType T>
	constexpr T DegToRad(const T& deg);

	template<ArithmeticType T>
	constexpr T RadIn2Pi(T rad);

	template<ArithmeticType T>
	constexpr T AngleDeg(const Vector3Template<T>& from, const Vector3Template<T>& to);

	template<typename  T>
	requires std::is_floating_point_v<T>
	constexpr bool FloatEqual(const T& val1, const T& val2);

	Quaternion AngleAxis(double rad, Vector3 axis);
}

#include "Details/MathHelper.h"
