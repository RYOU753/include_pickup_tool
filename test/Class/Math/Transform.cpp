#include "Transform.h"
#include "MathDefinition.h"

namespace Kirara::Math
{

	Transform::Transform(void)
	{
	}

	Transform::Transform(Vector3 pos, Quaternion rot, Vector3 scale)
	{
		SetLocalPosition(pos);
		SetLocalRot(rot);
		SetLocalScale(scale);
	}

	bool Transform::SetParent(TransformOptRef parent)
	{
		if(IsCirculationParent(parent))
		{
			return false;
		}

		parent_ = parent;
		return true;
	}

	void Transform::SetLocalScale(Vector3 scale)
	{
		scale_ = scale;
	}

	void Transform::SetLocalPosition(Vector3 pos)
	{
		pos_ = pos;
	}

	void Transform::SetLocalRot(Quaternion rot)
	{
		rot_ = rot;
	}

	void Transform::SetLocalRotX(float rotX)
	{
		auto eulerRot = rot_.ToEuler();
		eulerRot.x = rotX;
		SetLocalRot(Quaternion::Euler(eulerRot));
	}

	void Transform::SetLocalRotY(float rotY)
	{
		auto eulerRot = rot_.ToEuler();
		eulerRot.y = rotY;
		SetLocalRot(Quaternion::Euler(eulerRot));
	}

	void Transform::SetLocalRotZ(float rotZ)
	{
		auto eulerRot = rot_.ToEuler();
		eulerRot.z = rotZ;
		SetLocalRot(Quaternion::Euler(eulerRot));
	}

	void Transform::AddLocalPosition(Vector3 vec)
	{
		pos_ += vec;
	}

	const Vector3& Transform::GetLocalScale(void) const
	{
		return scale_;
	}

	const Vector3& Transform::GetLocalPosition(void) const
	{
		return pos_;
	}

	const Quaternion& Transform::GetLocalRot(void) const
	{
		return rot_;
	}

	Vector3 Transform::GetWorldScale(void) const
	{
		Vector3 result = scale_;

		if (parent_)
		{
			result *= parent_->get().GetWorldScale();
		}

		return result;
	}

	Vector3Flt Transform::GetWorldPosition(void) const
	{
		Vector3 result = pos_;

		if (parent_)
		{
			result = parent_->get().GetWorldPosition() + GetWorldRot().PosAxis(pos_ * GetWorldScale());
		}

		return result;
	}

	Quaternion Transform::GetWorldRot(void) const
	{
		Quaternion result = rot_;

		if (parent_)
		{
			result = parent_->get().GetWorldRot().Multiply(result);
		}

		return result;
	}

	Vector3Flt Transform::GetForward(void)const
	{
		return GetDir(DIR_FORWARD<>);
	}

	Vector3Flt Transform::GetBack(void)const
	{
		return GetDir(DIR_BACK<>);
	}

	Vector3Flt Transform::GetRight(void)const
	{
		return GetDir(DIR_RIGHT<>);
	}

	Vector3Flt Transform::GetLeft(void)const
	{
		return GetDir(DIR_LEFT<>);
	}

	Vector3Flt Transform::GetUp(void)const
	{
		return GetDir(DIR_UP<>);
	}

	Vector3Flt Transform::GetDown(void)const
	{
		return GetDir(DIR_DOWN<>);
	}

	Vector3Flt Transform::GetDir(const Vector3Flt& vec)const
	{
		return GetWorldRot().PosAxis(vec).Normalized();
	}

	bool Transform::IsCirculationParent(TransformOptRef parent)const
	{
		if(parent.has_value())
		{
			//自分自身かをチェック
			if(&(parent->get()) == this)
			{
				return true;
			}
			//親を遡っていく中で自身がいないかをチェック
			auto p = parent->get().parent_;
			for(;p.has_value();p = p->get().parent_)
			{
				if (&(p->get()) == this)
				{
					return true;
				}
			}
		}
		
		return false;
	}

	Transform& Transform::GetRootParent(void)
	{
		if (!parent_)
		{
			return *this;
		}

		return parent_->get().GetRootParent();
	}

}
