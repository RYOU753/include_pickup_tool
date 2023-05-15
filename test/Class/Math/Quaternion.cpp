#include "MathDefinition.h"
#include "MathHelper.h"
#include "Quaternion.h"

namespace Kirara::Math
{
	Quaternion Quaternion::Identity(void)
	{
		return { 1.0, 0.0, 0.0, 0.0 };
	}

	Quaternion Quaternion::Euler(Vector3 euler)
	{
		Quaternion ret;

		euler.x = RadIn2Pi(euler.x);
		euler.y = RadIn2Pi(euler.y);
		euler.z = RadIn2Pi(euler.z);

		euler = euler / 2.0f;

		const auto cosX = static_cast<double>(cos(euler.x));
		const auto sinX = static_cast<double>(sin(euler.x));
		const auto cosY = static_cast<double>(cos(euler.y));
		const auto sinY = static_cast<double>(sin(euler.y));
		const auto cosZ = static_cast<double>(cos(euler.z));
		const auto sinZ = static_cast<double>(sin(euler.z));

		ret.w = cosX * cosY * cosZ + sinX * sinY * sinZ;
		ret.x = sinX * cosY * cosZ + cosX * sinY * sinZ;
		ret.y = cosX * sinY * cosZ - sinX * cosY * sinZ;
		ret.z = cosX * cosY * sinZ - sinX * sinY * cosZ;

		return ret;
	}

	Vector3 Quaternion::ToEuler(void)const
	{
		Vector3Dbl ret;

		const auto r11 = 2.0 * (x * z + w * y);
		const auto r12 = w * w - x * x - y * y + z * z;
		const auto r21 = -2.0 * (y * z - w * x);
		const auto r31 = 2.0 * (x * y + w * z);
		const auto r32 = w * w - x * x + y * y - z * z;

		ret.x = asin(r21);
		ret.y = atan2(r11, r12);
		ret.z = atan2(r31, r32);

		return static_cast<Vector3>(ret);
	}

	constexpr Quaternion Quaternion::Multiply(const Quaternion& q)const
	{
		auto ret = Quaternion();

		// wの計算 
		double d1 = w * q.w;
		double d2 = -x * q.x;
		double d3 = -y * q.y;
		double d4 = -z * q.z;
		ret.w = d1 + d2 + d3 + d4;

		// xの計算 
		d1 = w * q.x;
		d2 = x * q.w;
		d3 = y * q.z;
		d4 = -z * q.y;
		ret.x = d1 + d2 + d3 + d4;

		// yの計算
		d1 = w * q.y;
		d2 = -x * q.z;
		d3 = y * q.w;
		d4 = z * q.x;
		ret.y = d1 + d2 + d3 + d4;

		// zの計算
		d1 = w * q.z;
		d2 = x * q.y;
		d3 = -y * q.x;
		d4 = z * q.w;
		ret.z = d1 + d2 + d3 + d4;

		return ret;
	}

	constexpr Vector3 Quaternion::PosAxis(const Vector3& pos)const
	{
		/*auto tmp = Quaternion();
		tmp = tmp.Multiply(*this);
		tmp = tmp.Multiply(Quaternion(0.0, static_cast<double>(pos.x), static_cast<double>(pos.y), static_cast<double>(pos.z)));
		tmp = tmp.Multiply((*this).Inverse());
		return { static_cast<Vector3::Type>(tmp.x), static_cast<Vector3::Type>(tmp.y), static_cast<Vector3::Type>(tmp.z) };*/
		return operator*(pos);
	}

	Quaternion Quaternion::LookRotation(Vector3 dir)
	{
		return LookRotation(dir, DIR_UP<Vector3::Type>);
	}

	Quaternion Quaternion::LookRotation(Vector3 dir, Vector3 up)
	{
		dir.Normalize();

		const auto right = up.Cross(dir).Normalized();
		up = dir.Cross(right);
		const auto m00 = static_cast<double>(right.x);
		const auto m01 = static_cast<double>(right.y);
		const auto m02 = static_cast<double>(right.z);
		const auto m10 = static_cast<double>(up.x);
		const auto m11 = static_cast<double>(up.y);
		const auto m12 = static_cast<double>(up.z);
		const auto m20 = static_cast<double>(dir.x);
		const auto m21 = static_cast<double>(dir.y);
		const auto m22 = static_cast<double>(dir.z);

		const auto num8 = m00 + m11 + m22;
		auto quaternion = Quaternion();

		if (num8 > 0.0)
		{
			double num = sqrt(num8 + 1.0);
			quaternion.w = num * 0.5;
			num = 0.5 / num;
			quaternion.x = (m12 - m21) * num;
			quaternion.y = (m20 - m02) * num;
			quaternion.z = (m01 - m10) * num;
			return quaternion.Normalized();
		}

		if ((m00 >= m11) && (m00 >= m22))
		{
			const auto num7 = sqrt(1.0 + m00 - m11 - m22);
			const auto num4 = 0.5 / num7;
			quaternion.x = (m12 - m21) * num4;
			quaternion.y = (m01 + m10) * num4;
			quaternion.z = (m02 + m20) * num4;
			quaternion.w = 0.5 * num7;
			return quaternion.Normalized();
		}

		if (m11 > m22)
		{
			const auto num6 = sqrt(((1.0 + m11) - m00) - m22);
			const auto num3 = 0.5 / num6;
			quaternion.x = (m10 + m01) * num3;
			quaternion.y = 0.5 * num6;
			quaternion.z = (m21 + m12) * num3;
			quaternion.w = (m20 - m02) * num3;
			return quaternion.Normalized();
		}

		const auto num5 = sqrt(((1.0 + m22) - m00) - m11);
		const auto num2 = 0.5 / num5;
		quaternion.x = (m20 + m02) * num2;
		quaternion.y = (m21 + m12) * num2;
		quaternion.z = 0.5 * num5;
		quaternion.w = (m01 - m10) * num2;
		return quaternion.Normalized();
	}

	Vector3 Quaternion::GetDir(Vector3 dir)const
	{
		return PosAxis(dir);
	}

	Vector3 Quaternion::GetForward(void)const
	{
		return GetDir(DIR_FORWARD<>);
	}

	Vector3 Quaternion::GetBack(void)const
	{
		return GetDir(DIR_BACK<>);
	}

	Vector3 Quaternion::GetRight(void)const
	{
		return GetDir(DIR_RIGHT<>);
	}

	Vector3 Quaternion::GetLeft(void)const
	{
		return GetDir(DIR_LEFT<>);
	}

	Vector3 Quaternion::GetUp(void)const
	{
		return GetDir(DIR_UP<>);
	}

	Vector3 Quaternion::GetDown(void)const
	{
		return GetDir(DIR_DOWN<>);
	}

	double Quaternion::Dot(const Quaternion& q)const
	{
		return (w * q.w + x * q.x + y * q.y + z * q.z);
	}

	Quaternion Quaternion::Normalized(void)const
	{
		auto ret = *this;
		ret.Normalize();
		return ret;
	}

	void Quaternion::Normalize(void)
	{
		const double mag = sqrt(w * w + x * x + y * y + z * z);

		w /= mag;
		x /= mag;
		y /= mag;
		z /= mag;
	}

	Quaternion Quaternion::Conjugate() const
	{
		return Quaternion{ w,-1. * x,-1. * y ,-1. * z };
	}

	Quaternion Quaternion::Inverse(void)const
	{
		const auto n = 1.0 / (w * w + x * x + y * y + z * z);
		const auto lensq = (w * w + x * x + y * y + z * z);
		const auto tmp = Conjugate();
		//return tmp * n;
		return Quaternion(tmp.w / lensq, tmp.x / lensq, tmp.y / lensq, tmp.z / lensq);
	}

	inline float SIGN(float x) {
		return (x >= 0.0f) ? +1.0f : -1.0f;
	}

	inline float NORM(float a, float b, float c, float d) {
		return sqrt(a * a + b * b + c * c + d * d);
	}

	Quaternion Quaternion::FromToRotation(Vector3 fromDir, Vector3 toDir)
	{
		Vector3 axis = fromDir.Cross(toDir);
		const auto angle = AngleDeg(fromDir, toDir);
		if (angle >= 179.9196f)
		{
			auto r = fromDir.Cross(DIR_RIGHT<>);
			axis = r.Cross(fromDir);

			if (axis.SqMagnitude() < 0.000001f)
			{
				axis = DIR_UP<>;
			}
		}

		axis.Normalize();
		return AngleAxis(DegToRad(static_cast<double>(angle)), axis);

	}

	Quaternion Quaternion::RotateTowards(Quaternion from, Quaternion to, float maxDegreesDelta)
	{
		double num = Angle(from, to);
		if (num == 0.0)
		{
			return to;
		}
		float t = std::min(1.0f, maxDegreesDelta / (float)num);
		return SlerpUnclamped(from, to, t);
	}

	double Quaternion::Angle(Quaternion q1, Quaternion q2)
	{
		const double cos = q1.Dot(q2);
		const double ac = acos(cos);
		return ac * 2.0 * 180.0 / std::numbers::pi;
	}

	Quaternion Quaternion::Slerp(Quaternion& from, Quaternion& to, float t)
	{
		if (t > 1) t = 1;
		if (t < 0) t = 0;
		return SlerpUnclamped(from, to, t);
	}

	Quaternion Quaternion::SlerpUnclamped(Quaternion& a, Quaternion& b, float t)
	{
		if (a.LengthSquared() == 0.0)
		{
			if (b.LengthSquared() == 0.0)
			{
				return Identity();
			}
			return b;
		}
		else if (b.LengthSquared() == 0.0)
		{
			return a;
		}


		float cosHalfAngle = static_cast<float>(a.w * b.w) + a.xyz().Dot(b.xyz());

		if (cosHalfAngle >= 1.0f || cosHalfAngle <= -1.0f)
		{
			return a;
		}
		else if (cosHalfAngle < 0.0f)
		{
			b.x = b.x * -1.0;
			b.y = b.y * -1.0;
			b.z = b.z * -1.0;
			b.w = -b.w;
			cosHalfAngle = -cosHalfAngle;
		}

		float blendA = 0.0f;
		float blendB = 0.0f;
		if (cosHalfAngle < 0.99f)
		{
			const float halfAngle = acos(cosHalfAngle);
			const float sinHalfAngle = sin(halfAngle);
			const float oneOverSinHalfAngle = 1.0f / sinHalfAngle;
			blendA = sin(halfAngle * (1.0f - t)) * oneOverSinHalfAngle;
			blendB = sin(halfAngle * t) * oneOverSinHalfAngle;
		}
		else
		{
			blendA = 1.0f - t;
			blendB = t;
		}
		
		const auto v = static_cast<Vector3Dbl>(a.xyz() * blendA + b.xyz() * blendB);
		const auto result = Quaternion(static_cast<double>(blendA) * a.w + static_cast<double>(blendB) * b.w, v.x, v.y, v.z);
		if (result.LengthSquared() > 0.0)
		{
			return Normalize(result);
		}

		return Identity();
	}

	double Quaternion::Length(void)const
	{
		return sqrt(x * x + y * y + z * z + w * w);
	}

	double Quaternion::LengthSquared(void)const
	{
		return x * x + y * y + z * z + w * w;
	}

	constexpr Vector3 Quaternion::xyz(void)const
	{
		return { static_cast<Vector3::Type>(x), static_cast<Vector3::Type>(y), static_cast<Vector3::Type>(z) };
	}

	Quaternion Quaternion::Normalize(Quaternion q)
	{
		Quaternion result = Quaternion();
		Normalize(q, result);
		return result;
	}

	void Quaternion::Normalize(Quaternion q, Quaternion& result)
	{
		const double scale = 1.0 / q.Length();
		const auto v = static_cast<Vector3Dbl>(q.xyz() * static_cast<float>(scale));
		result = Quaternion(q.w * scale, v.x, v.y, v.z);
	}

	void Quaternion::ToAngleAxis(float& angle, Vector3Flt& axis)
	{
		if (abs(w) > 1.0)
		{
			Normalize();
		}
		angle = 2.0f * acosf(static_cast<float>(w));

		if (x == 0.0 && y == 0.0 && z == 0.0)
		{
			angle = 0.0f;
		}

		const float den = sqrtf(1.0f - static_cast<float>(w * w));
		if (den > 0.0001f)
		{
			axis = xyz() / den;
		}
		else
		{
			axis = { 1.0f, 0.0f, 0.0f };
		}
	}

	constexpr Quaternion Quaternion::operator-() const
	{
		return Quaternion{ -w,-x,-y,-z };
	}

	constexpr Quaternion Quaternion::operator*(const double& rhs)const
	{
		return Quaternion{ w * rhs, x * rhs, y * rhs, z * rhs };
	}

	constexpr Vector3 Quaternion::operator*(const Vector3& rhs) const
	{
		return ((*this) * Quaternion(0., rhs) * (*this).Inverse()).xyz();
	}

	constexpr Quaternion Quaternion::operator+(const Quaternion& rhs)const
	{
		return Quaternion{ w + rhs.w, x + rhs.x, y + rhs.y, z + rhs.z };
	}

	constexpr Quaternion Quaternion::operator-(const Quaternion& rhs) const
	{
		return Quaternion{ w - rhs.w, x - rhs.x, y - rhs.y, z - rhs.z };
	}

	constexpr Quaternion Quaternion::operator*(const Quaternion& rhs) const
	{
		return Multiply(rhs);
	}

	bool Quaternion::operator==(const Quaternion& rhs)const
	{
		return FloatEqual(w, rhs.w) && FloatEqual(x, rhs.x) && FloatEqual(y, rhs.y) && FloatEqual(z, rhs.z);
	}

}
