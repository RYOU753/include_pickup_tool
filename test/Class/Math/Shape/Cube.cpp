#include "Cube.h"
#include "../MathDefinition.h"

namespace Kirara::Math
{
	Cube::Cube(const float& side)
	{
		transform_.SetLocalScale(VECTOR3_ONE<>*side);
	}

	Cube::Cube(const Vector3& pos, const float& side)
	{
		transform_.SetLocalPosition(pos);
		transform_.SetLocalScale(VECTOR3_ONE<>*side);
	}

	Cube::Cube(const float& width, const float& height, const float& depth)
	{
		transform_.SetLocalScale(Vector3{ width,height,depth });
	}

	Cube::Cube(const Vector3& pos, const float& width, const float& height, const float& depth)
	{
		transform_.SetLocalPosition(pos);
		transform_.SetLocalScale(Vector3{ width,height,depth });
	}

	float Cube::GetWidth() const
	{
		return transform_.GetWorldScale().x;
	}

	Cube& Cube::SetWidth(const float& width)
	{
		auto scl = transform_.GetLocalScale();
		scl.x = width;
		transform_.SetLocalScale(scl);
		return *this;
	}

	float Cube::GetHeight() const
	{
		return transform_.GetWorldScale().y;
	}

	Cube& Cube::SetHeight(const float& height)
	{
		auto scl = transform_.GetLocalScale();
		scl.y = height;
		transform_.SetLocalScale(scl);
		return *this;
	}

	float Cube::GetDepth() const
	{
		return transform_.GetWorldScale().z;
	}

	Cube& Cube::SetDepth(const float& depth)
	{
		auto scl = transform_.GetLocalScale();
		scl.z = depth;
		transform_.SetLocalScale(scl);
		return *this;
	}

	Cube& Cube::SetWHD(const float& width, const float& height, const float& depth)
	{
		Vector3 scl(width, height, depth);
		transform_.SetLocalScale(scl);
		return *this;
	}


	std::vector<Vector3> Cube::GetVertexes()
	{
		std::vector<Vector3> vertexes;
		vertexes.reserve(8);

		const auto pos = GetWorldPos();
		const auto scale = GetWorldScale() / 2.f;
		const auto rot = GetWorldRot();

		const auto top = rot.GetUp()* scale.y;
		const auto bottom = rot.GetDown()* scale.y;
		const auto left = rot.GetLeft()* scale.x;
		const auto right = rot.GetRight()* scale.x;
		const auto forward = rot.GetForward()* scale.z;
		const auto back = rot.GetBack()* scale.z;

		vertexes.emplace_back(pos + top + left + forward);
		vertexes.emplace_back(pos + top + right + forward);
		vertexes.emplace_back(pos + top + left + back);
		vertexes.emplace_back(pos + top + right + back);
		vertexes.emplace_back(pos + bottom + left + forward);
		vertexes.emplace_back(pos + bottom + right + forward);
		vertexes.emplace_back(pos + bottom + left + back);
		vertexes.emplace_back(pos + bottom + right + back);

		return vertexes;
	}

	std::vector<int> Cube::GetVertexIndexes()
	{
		Mesh::VertexIndexesType indexes = {
			0,1,2,//上面
			3,2,1,
			5,1,4,//後面
			0,4,1,
			0,2,4,//左面
			6,4,2,
			3,7,2,//前面
			6,2,7,
			1,5,3,//右面
			7,3,5,
			6,7,4,//下面
			5,4,7
		};
		return indexes;
	}

	Mesh Cube::GetMesh()
	{
		Mesh mesh(GetVertexes(),GetVertexIndexes());
		return mesh;
	}
}
