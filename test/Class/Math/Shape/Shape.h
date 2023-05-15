#pragma once
#include <vector>
#include "../Transform.h"
#include "../Mesh.h"

namespace Kirara::Math
{
	class Shape
	{
	public:
		Shape() = default;
		virtual ~Shape() = default;

		[[nodiscard]]
		const Vector3& GetLocalPos(void)const;

		Shape& SetLocalPos(const Vector3& pos);

		[[nodiscard]]
		const Quaternion& GetLocalRot(void)const;

		Shape& SetLocalRot(const Quaternion& rot);

		[[nodiscard]]
		const Vector3& GetLocalScale(void)const;

		Shape& SetLocalScale(const Vector3& scl);

		[[nodiscard]]
		virtual const Transform& GetTransform(void)const;

		virtual void SetTransform(const Transform& transform);

		[[nodiscard]]
		Vector3 GetWorldPos(void)const;

		[[nodiscard]]
		Quaternion GetWorldRot(void)const;

		[[nodiscard]]
		Vector3 GetWorldScale(void)const;

		[[nodiscard]]
		virtual std::vector<Vector3> GetVertexes(void) = 0;

		[[nodiscard]]
		virtual std::vector<int> GetVertexIndexes(void) = 0;

		[[nodiscard]]
		virtual Mesh GetMesh(void) = 0;
	protected:
		Transform transform_;
	};
}
