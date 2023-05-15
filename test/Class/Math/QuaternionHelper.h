#pragma once
#include "Quaternion.h"
#include "../common/Utility.h"

namespace Kirara::Math::QuaternionHelper
{
	/// <summary>
	/// それぞれのオイラー角からクォータニオンを生成
	/// </summary>
	/// <typeparam name="T">任意の型</typeparam>
	/// <param name="x">X角</param>
	/// <param name="y">Y角</param>
	/// <param name="z">Z角</param>
	/// <returns>生成後のクォータニオン</returns>
	template<class T>
	Quaternion Euler(const T& x, const T& y, const T& z)
	{
        Quaternion ret = Quaternion();

        auto radIn2PI = Utility::RadIn2PI();

        float radX = radIn2PI(x);
        float radY = radIn2PI(y);
        float radZ = radIn2PI(z);

        double cosZ = cos(radZ / 2.0f);
        double sinZ = sin(radZ / 2.0f);
        double cosX = cos(radX / 2.0f);
        double sinX = sin(radX / 2.0f);
        double cosY = cos(radY / 2.0f);
        double sinY = sin(radY / 2.0f);

        ret.w = cosX * cosY * cosZ + sinX * sinY * sinZ;
        ret.x = sinX * cosY * cosZ + cosX * sinY * sinZ;
        ret.y = cosX * sinY * cosZ - sinX * cosY * sinZ;
        ret.z = cosX * cosY * sinZ - sinX * sinY * cosZ;

        return ret;
	}

	/// <summary>
	/// オイラー角からクォータニオンを生成
	/// </summary>
	/// <param name="vec">オイラー角</param>
	/// <returns>生成後のクォータニオン</returns>
	Quaternion Euler(const VECTOR& vec)
	{
		return Euler(vec.x, vec.y, vec.z);
	}

    /// <summary>
    /// クォータニオンの合成
    /// </summary>
    /// <param name="q1">合成されるクォータニオン</param>
    /// <param name="q2">合成するクォータニオン</param>
    /// <returns>合成後のクォータニオン</returns>
    Quaternion Mult(const Quaternion& q1, const Quaternion& q2)
    {
        Quaternion ret = Quaternion();
        double d1, d2, d3, d4;

        // wの計算 
        d1 = q1.w * q2.w;
        d2 = -q1.x * q2.x;
        d3 = -q1.y * q2.y;
        d4 = -q1.z * q2.z;
        ret.w = d1 + d2 + d3 + d4;

        // xの計算 
        d1 = q1.w * q2.x;
        d2 = q2.w * q1.x;
        d3 = q1.y * q2.z;
        d4 = -q1.z * q2.y;
        ret.x = d1 + d2 + d3 + d4;

        // yの計算
        d1 = q1.w * q2.y;
        d2 = q2.w * q1.y;
        d3 = q1.z * q2.x;
        d4 = -q1.x * q2.z;
        ret.y = d1 + d2 + d3 + d4;

        // zの計算
        d1 = q1.w * q2.z;
        d2 = q2.w * q1.z;
        d3 = q1.x * q2.y;
        d4 = -q1.y * q2.x;
        ret.z = d1 + d2 + d3 + d4;

        return ret;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="rad"></param>
    /// <param name="axis"></param>
    /// <returns></returns>
    Quaternion AngleAxis(const double& rad, const VECTOR& axis)
    {
        VECTOR_D axisD = VGetD(static_cast<double>(axis.x), static_cast<double>(axis.y), static_cast<double>(axis.z));

        Quaternion ret = Quaternion();

        double norm = VDotD(axisD, axisD);

        if (norm <= 0.0)
        {
            return ret;
        }

        norm = 1.0 / sqrt(norm);
        
        axisD = VScaleD(axisD, norm);

        double c = cos(0.5 * rad);
        double s = sin(0.5 * rad);

        ret.w = c;
        ret.x = s * axisD.x;
        ret.y = s * axisD.y;
        ret.z = s * axisD.z;

        return ret;
    }
}
