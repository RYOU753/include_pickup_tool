#pragma once
#include <BulletPhysics/LinearMath/btQuaternion.h>
#include "Math/Quaternion.h"

namespace Kirara::Math::Helper
{
	inline btVector3 Vector3ToBtVector3(const Vector3& v)
	{
		return btVector3{ static_cast<btScalar>(v.x),static_cast<btScalar>(v.y),static_cast<btScalar>(v.z) };
	}

	inline btQuaternion QuaternionToBtQuaternion(const Quaternion& q)
	{
		return { q.x, q.y, q.z, q.w };
	}
}