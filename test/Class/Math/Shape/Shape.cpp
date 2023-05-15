#include "Shape.h"

namespace Kirara::Math
{
	const Vector3& Shape::GetLocalPos() const
	{
		return transform_.GetLocalPosition();
	}

	Shape& Shape::SetLocalPos(const Vector3& pos)
	{
		transform_.SetLocalPosition(pos);
		return *this;
	}

	const Quaternion& Shape::GetLocalRot() const
	{
		return transform_.GetLocalRot();
	}

	Shape& Shape::SetLocalRot(const Quaternion& rot)
	{
		transform_.SetLocalRot(rot);
		return *this;
	}

	const Vector3& Shape::GetLocalScale() const
	{
		return transform_.GetLocalScale();
	}

	Shape& Shape::SetLocalScale(const Vector3& scl)
	{
		transform_.SetLocalScale(scl);
		return *this;
	}

	const Transform& Shape::GetTransform(void)const
	{
		return transform_;
	}

	void Shape::SetTransform(const Transform& transform)
	{
		transform_ = transform;
	}
	Vector3 Shape::GetWorldPos(void) const
	{
		return transform_.GetWorldPosition();
	}
	Quaternion Shape::GetWorldRot(void) const
	{
		return transform_.GetWorldRot();
	}
	Vector3 Shape::GetWorldScale(void) const
	{
		return transform_.GetWorldScale();
	}
}
