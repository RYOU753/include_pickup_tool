#pragma once

namespace Kirara::Math
{
	template <typename T>
	class Vector2Template
	{
	public:
		using Type = T;

		constexpr Vector2Template() :x(0), y(0) {}
		constexpr Vector2Template(T x, T y) :x(x), y(y) {}

		constexpr ~Vector2Template() = default;

		T x;
		T y;

		/// @brief ベクトルの大きさを取得
		/// @return ベクトルの大きさ
		[[nodiscard]]
		constexpr T Magnitude(void)const;

		/// @brief ベクトルの大きさの二乗を取得
		/// @return ベクトルの大きさの二乗
		[[nodiscard]]
		constexpr T SqMagnitude(void)const;

		[[nodiscard]]
		constexpr T Distance(const Vector2Template& vec)const;

		/// @brief 正規化
		void Normalize(void);

		/// @brief 正規化済みベクトルを取得
		/// @return 正規化済みベクトル
		[[nodiscard]]
		constexpr Vector2Template Normalized(void)const;

		/// @brief ラジアン値による回転
		/// @param rad ラジアン値
		/// @return 回転済みベクトル
		[[nodiscard]]
		constexpr Vector2Template RotateByRad(double rad)const;

		/// @brief 度数による回転
		/// @param deg 度数
		/// @return 回転済みvector
		[[nodiscard]]
		constexpr Vector2Template RotateByDeg(double deg)const;

		/// @brief 内積
		/// @param vec もう一つのベクトル
		/// @return 内積値
		[[nodiscard]]
		constexpr T Dot(const Vector2Template& vec)const;

		/// @brief 外積
		/// @param vec もう一つのベクトル
		/// @return 外積値
		[[nodiscard]]
		constexpr T Cross(const Vector2Template& vec)const;

		/// @brief x * y　の取得
		/// @return x * y
		[[nodiscard]]
		constexpr T Area(void)const;

		/// @brief 反射
		/// @param nVec 法線ベクトル
		/// @return 反射ベクトル
		[[nodiscard]]
		constexpr Vector2Template Reflect(Vector2Template nVec)const;

		//代入演算子
		Vector2Template& operator=(const Vector2Template& vec);

		//添字演算子
		T& operator[](int num);

		//単項演算子
		Vector2Template& operator+=(const Vector2Template& vec);
		Vector2Template& operator+=(const T& num);
		Vector2Template& operator-=(const Vector2Template& vec);
		Vector2Template& operator*=(const Vector2Template& vec);
		Vector2Template& operator/=(const Vector2Template& vec);
		Vector2Template& operator%=(const Vector2Template& vec);
		constexpr Vector2Template operator+()const;
		constexpr Vector2Template operator-()const;

		//二項演算子
		constexpr Vector2Template operator+(Vector2Template vec)const;
		constexpr Vector2Template operator-(Vector2Template vec)const;
		constexpr Vector2Template operator*(Vector2Template vec)const;
		constexpr Vector2Template operator/(Vector2Template vec)const;
		constexpr Vector2Template operator%(Vector2Template vec)const;

		//比較演算子
		constexpr bool operator==(const Vector2Template& vec)const;
		constexpr bool operator!=(const Vector2Template& vec)const;
		constexpr bool operator<(const Vector2Template& vec)const;
		constexpr bool operator<=(const Vector2Template& vec)const;
		constexpr bool operator>(const Vector2Template& vec)const;
		constexpr bool operator>=(const Vector2Template& vec)const;

		//cast演算子
		explicit constexpr operator Vector2Template<int>()const { return { static_cast<int>(this->x),static_cast<int>(this->y) }; }
		explicit constexpr operator Vector2Template<float>()const { return { static_cast<float>(this->x),static_cast<float>(this->y) }; }
		explicit constexpr operator Vector2Template<double>()const { return { static_cast<double>(this->x),static_cast<double>(this->y) }; }

		constexpr Vector2Template(const Vector2Template&) = default;
		constexpr Vector2Template(Vector2Template&&) = default;
		constexpr Vector2Template& operator=(Vector2Template&&) = default;
	};

	template<typename T>
	constexpr Vector2Template<T> operator+(const Vector2Template<T>& vec, T num);

	template<typename T>
	constexpr Vector2Template<T> operator+(T num, const Vector2Template<T>& vec);

	template<typename T>
	constexpr Vector2Template<T> operator-(const Vector2Template<T>& vec, T num);

	template<typename T>
	constexpr Vector2Template<T> operator-(T num, const Vector2Template<T>& vec);

	template<typename T>
	constexpr Vector2Template<T> operator*(const Vector2Template<T>& vec, T num);

	template<typename T>
	constexpr Vector2Template<T> operator*(T num, const Vector2Template<T>& vec);

	template<typename T>
	constexpr Vector2Template<T> operator/(const Vector2Template<T>& vec, T num);

	template<typename T>
	constexpr Vector2Template<T> operator%(const Vector2Template<T>& vec, T num);

	template<typename T>
	constexpr Vector2Template<T> RotateByDeg(const Vector2Template<T>& center, const Vector2Template<T>& pos, double deg);

	template<typename T>
	constexpr Vector2Template<T> RotateByRad(const Vector2Template<T>& center, const Vector2Template<T>& pos, double rad);

	using Vector2Int = Vector2Template<int>;
	using Vector2Flt = Vector2Template<float>;
	using Vector2Dbl = Vector2Template<double>;

	using Vector2 = Vector2Flt;
}

#include "Details/Vector2.h"
