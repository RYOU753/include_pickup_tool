#pragma once

namespace Kirara::Math
{
	template <class T> 
	class Vector3Template
	{
	public:
		using Type = T;

		constexpr Vector3Template() :x(0), y(0), z(0) {}
		constexpr Vector3Template(T x, T y, T z) :x(x), y(y), z(z) {}

		T x;
		T y;
		T z;

		/// @brief ベクトルの大きさを取得
		/// @return ベクトルの大きさ
		[[nodiscard]]
		constexpr T Magnitude(void)const;

		/// @brief ベクトルの大きさの二乗を取得
		/// @return ベクトルの大きさの二乗
		[[nodiscard]]
		constexpr T SqMagnitude(void)const;

		[[nodiscard]]
		constexpr T Distance(const Vector3Template& vec)const;

		/// @brief 正規化
		void Normalize(void);

		/// @brief 正規化済みベクトルを取得
		/// @return 正規化済みベクトル
		[[nodiscard]]
		constexpr Vector3Template Normalized(void)const;

		/// @brief 内積
		/// @param vec もう一つのベクトル
		/// @return 内積値
		[[nodiscard]]
		constexpr T Dot(const Vector3Template& vec)const;

		/// @brief 外積
		/// @param vec もう一つのベクトル
		/// @return 外積値
		[[nodiscard]]
		constexpr Vector3Template Cross(const Vector3Template& vec)const;

		/// @brief x * y * zを取得
		/// @return x * y * z
		[[nodiscard]]
		constexpr T Area(void)const;

		/// @brief 反射
		/// @param nVec 法線ベクトル
		/// @return 反射ベクトル
		[[nodiscard]]
		constexpr Vector3Template Reflect(const Vector3Template& nVec)const;

		//代入演算子
		Vector3Template& operator=(const Vector3Template&);

		//添字演算子
		T& operator[](int num);

		//単項演算子
		Vector3Template& operator+=(const Vector3Template& vec);
		Vector3Template& operator+=(const T& num);
		Vector3Template& operator-=(const Vector3Template& vec);
		Vector3Template& operator*=(const Vector3Template& vec);
		Vector3Template& operator/=(const Vector3Template& vec);
		Vector3Template& operator%=(const Vector3Template& vec);
		constexpr Vector3Template operator+()const;
		constexpr Vector3Template operator-()const;

		//二項演算子
		constexpr Vector3Template operator+(const Vector3Template& vec)const;
		constexpr Vector3Template operator-(const Vector3Template& vec)const;
		constexpr Vector3Template operator*(const Vector3Template& vec)const;
		constexpr Vector3Template operator/(const Vector3Template& vec)const;
		constexpr Vector3Template operator%(const Vector3Template& vec)const;

		//比較演算子
		constexpr bool operator==(const Vector3Template& vec)const;
		constexpr bool operator!=(const Vector3Template& vec)const;
		constexpr bool operator<(const Vector3Template& vec)const;
		constexpr bool operator<=(const Vector3Template& vec)const;
		constexpr bool operator>(const Vector3Template& vec)const;
		constexpr bool operator>=(const Vector3Template& vec)const;

		template<class Vec>
		Vector3Template& operator()(const Vec& vec);

		//cast演算子
		explicit constexpr operator Vector3Template<int>()const { return { static_cast<int>(this->x),static_cast<int>(this->y),static_cast<int>(this->z) }; }
		explicit constexpr operator Vector3Template<float>()const { return { static_cast<float>(this->x),static_cast<float>(this->y),static_cast<float>(this->z) }; }
		explicit constexpr operator Vector3Template<double>()const { return { static_cast<double>(this->x),static_cast<double>(this->y),static_cast<double>(this->z) }; }
	};
	template<class T> constexpr
		Vector3Template<T> operator+(const Vector3Template<T>& vec, const T& num);

	template<class T> constexpr
		Vector3Template<T> operator+(const T& num, const Vector3Template<T>& vec);

	template<class T> constexpr
		Vector3Template<T> operator-(const Vector3Template<T>& vec, const T& num);

	template<class T> constexpr
		Vector3Template<T> operator-(const T& num, const Vector3Template<T>& vec);

	template<class T> constexpr
		Vector3Template<T> operator*(const Vector3Template<T>& vec, const T& num);

	template<class T> constexpr
		Vector3Template<T> operator*(const T& num, const Vector3Template<T>& vec);

	template<class T> constexpr
		Vector3Template<T> operator/(const Vector3Template<T>& vec, const T& num);

	template<class T> constexpr
		Vector3Template<T> operator%(const Vector3Template<T>& vec, const T& num);

	using Vector3Int = Vector3Template<int>;
	using Vector3Flt = Vector3Template<float>;
	using Vector3Dbl = Vector3Template<double>;

	using Vector3 = Vector3Flt;
}

#include "Details/Vector3.h"
