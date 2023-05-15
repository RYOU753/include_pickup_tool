#pragma once
#include <numbers>

#include "Vector2.h"
#include "Vector3.h"

namespace Kirara::Math
{
	using DefinitionArithmeticType = float;

	template<class T>
	concept ArithmeticType = requires()
	{
		std::is_arithmetic_v<T>;
	};
	template<ArithmeticType T = DefinitionArithmeticType>
	constexpr Vector2Template<T> VECTOR2_ZERO = { 0, 0 };

	template<ArithmeticType T = DefinitionArithmeticType>
	constexpr Vector2Template<T> VECTOR2_ONE = { 1, 1 };

	template<ArithmeticType T = DefinitionArithmeticType>
	constexpr Vector3Template<T> VECTOR3_ZERO = {  0, 0, 0 };

	template<ArithmeticType T = DefinitionArithmeticType>
	constexpr Vector3Template<T> VECTOR3_ONE = {  1, 1, 1 };

	// 方向
	template<ArithmeticType T = DefinitionArithmeticType>
	constexpr Vector3Template<T> DIR_FORWARD = { 0, 0, 1 };

	template<ArithmeticType T = DefinitionArithmeticType>
	constexpr Vector3Template<T> DIR_BACK = { 0, 0, -1 };

	template<ArithmeticType T = DefinitionArithmeticType>
	constexpr Vector3Template<T> DIR_RIGHT = { 1, 0, 0 };

	template<ArithmeticType T = DefinitionArithmeticType>
	constexpr Vector3Template<T> DIR_LEFT = { -1, 0, 0 };

	template<ArithmeticType T = DefinitionArithmeticType>
	constexpr Vector3Template<T> DIR_UP = { 0, 1, 0 };

	template<ArithmeticType T = DefinitionArithmeticType>
	constexpr Vector3Template<T> DIR_DOWN = { 0, -1, 0 };

	template<ArithmeticType T = DefinitionArithmeticType>
	constexpr Vector3Template<T> AXIS_X = { 1, 0, 0 };

	template<ArithmeticType T = DefinitionArithmeticType>
	constexpr Vector3Template<T> AXIS_Y = { 0, 1, 0 };

	template<ArithmeticType T = DefinitionArithmeticType>
	constexpr Vector3Template<T> AXIS_Z = { 0, 0, 1 };

	constexpr float K_EPSILON_NORMAL_SQRT = 1e-15F;
}
