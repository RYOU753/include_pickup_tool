#pragma once
#include "../Math/Vector3.h"

namespace Kirara::Math
{
	class Quaternion
	{
	public:
		double w;
		double x;
		double y;
		double z;

		constexpr Quaternion(void) :w(1.0), x(0.0), y(0.0), z(0.0) {}
		constexpr Quaternion(const double& w, const double& x, const double& y, const double& z) :w(w), x(x), y(y), z(z) {}
		constexpr Quaternion(const double& w, const Vector3& vec):w(w),x(static_cast<double>(vec.x)),y(static_cast<double>(vec.y)),z(static_cast<double>(vec.z)){}
		[[nodiscard]]
		static Quaternion Identity(void);
		
		/// @brief オイラー角からクオータニオンへ変換
		/// @param euler (x:rad,y:rad,z:rad)
		/// @return オイラー角を変換したクオータニオン
		[[nodiscard]]
		static Quaternion Euler(Vector3 euler);
		
		/// @brief クォータニオンからオイラー角へ変換
		/// @return クォータニオンを変換したオイラー角
		[[nodiscard]]
		Vector3 ToEuler(void)const;
		
		/// @brief クォータニオンの合成
		/// @param q 合成するクォータニオン
		/// @return 合成したクオータニオン
		[[nodiscard]]
		constexpr Quaternion Multiply(const Quaternion& q)const;
		
		/// @brief 位置ベクトルを回転させる
		/// @param pos 回転させる座標
		/// @return 回転後の座標
		[[nodiscard]]
		constexpr Vector3 PosAxis(const Vector3& pos)const;
		
		/// @brief 特定の方向を見るクオータニオンを作成する(上が天井)
		/// @param dir 見たい方向
		/// @return 特定の方向を見るクオータニオン
		[[nodiscard]]
		static Quaternion LookRotation(Vector3 dir);

		/// @brief 特定の方向を見るクオータニオンを作成する
		/// @param dir 見たい方向
		/// @param up 上にするベクトル
		/// @return 特定の方向を見るクオータニオン 
		[[nodiscard]]
		static Quaternion LookRotation(Vector3 dir, Vector3 up);

		// 基本ベクトルを取得
		[[nodiscard]]
		Vector3 GetForward(void)const;

		[[nodiscard]]
		Vector3 GetBack(void)const;

		[[nodiscard]]
		Vector3 GetRight(void)const;

		[[nodiscard]]
		Vector3 GetLeft(void)const;

		[[nodiscard]]
		Vector3 GetUp(void)const;

		[[nodiscard]]
		Vector3 GetDown(void)const;

		[[nodiscard]]
		double Dot(const Quaternion& q)const;

		// 正規化
		[[nodiscard]]
		Quaternion Normalized(void)const;

		void Normalize(void);

		// 共役クオータニオン
		[[nodiscard]]
		Quaternion Conjugate(void)const;

		// 逆クォータニオン
		[[nodiscard]]
		Quaternion Inverse(void)const;
		
		/// @brief ２つのベクトル間の回転量を取得する
		/// @param fromDir 始めのベクトル
		/// @param toDir 終わりのベクトル
		/// @return ２つベクトル間の回転クオータニオンを取得
		[[nodiscard]]
		static Quaternion FromToRotation(Vector3Flt fromDir, Vector3Flt toDir);

		/// @brief 二つのクオータニオン間のクオータニオンを取得する
		/// @param from 始めのクオータニオン
		/// @param to 終わりのクオータニオン
		/// @param maxDegreesDelta 1回で進む角度(Deg)
		/// @return 二つのクオータニオン間のクオータニオン
		[[nodiscard]]
		static Quaternion RotateTowards(Quaternion from, Quaternion to, float maxDegreesDelta);

		/// @brief クオータニオン間の角度を取得する
		/// @param q1 間の角度を求めたいクオータニオン１
		/// @param q2 間の角度を求めたいクオータニオン２
		/// @return 間の角度(Deg)
		[[nodiscard]]
		static double Angle(Quaternion q1, Quaternion q2);

		// 球面補間
		[[nodiscard]]
		static Quaternion Slerp(Quaternion& from, Quaternion& to, float t);

		/// @brief クオータニオンからクオータニオンへの球面補完したクオータニオンを取得する
		/// @param a 始めのクオータニオン
		/// @param b 終わりのクオータニオン
		/// @param t 間を表すパラメータ
		/// @return クオータニオンからクオータニオンへの球面補完したクオータニオン
		[[nodiscard]]
		static Quaternion SlerpUnclamped(Quaternion& a, Quaternion& b, float t);

		// 対象方向の回転
		[[nodiscard]]
		double Length(void)const;

		[[nodiscard]]
		double LengthSquared(void)const;

		[[nodiscard]]
		constexpr Vector3 xyz(void)const;

		[[nodiscard]]
		static Quaternion Normalize(Quaternion q);

		static void Normalize(Quaternion q, Quaternion& result);

		/// @brief  Quaternionの回転角度と回転軸を取得する
		/// @param angle 出力(回転角度)
		/// @param axis 出力(回転軸)
		void ToAngleAxis(float& angle, Vector3& axis);

		
		constexpr Quaternion operator-(void)const;
		constexpr Quaternion operator*(const double& rhs)const;
		constexpr Vector3 operator*(const Vector3& rhs)const;
		constexpr Quaternion operator+(const Quaternion& rhs)const;
		constexpr Quaternion operator-(const Quaternion& rhs)const;
		constexpr Quaternion operator*(const Quaternion& rhs)const;
		bool operator==(const Quaternion&) const;
	private:

		// 基本ベクトルを取得
		Vector3 GetDir(Vector3 dir)const;
	};
}
