#include "Capsule.h"

namespace Kirara::Math
{
	Capsule::Capsule(float radius, float height)
	{
		transform_.SetLocalScale(Vector3{ radius,height,radius });
	}

	float Capsule::GetRadius() const
	{
		return transform_.GetWorldScale().x;
	}

	Capsule& Capsule::SetRadius(const float& radius)
	{
		auto scl = GetLocalScale();
		scl.x = radius;
		scl.z = radius;
		transform_.SetLocalScale(scl);
		return *this;
	}

	float Capsule::GetHeight()const
	{
		return GetWorldScale().y;
	}

	Capsule& Capsule::SetHeight(const float& height)
	{
		auto scl = GetLocalScale();
		scl.y = height;
		transform_.SetLocalScale(scl);
		return *this;
	}

	Vector3 Capsule::GetTop()const
	{
		return GetWorldPos() + GetWorldRot().GetUp() * (GetWorldScale().y / 2.f);
	}

	Vector3 Capsule::GetBottom()const
	{
		return GetWorldPos() + GetWorldRot().GetDown() * (GetWorldScale().y / 2.f);
	}

	Vector3 Capsule::GetTopSpherePos() const
	{
		const auto scl = GetWorldScale();
		return GetWorldPos() + GetWorldRot().GetUp() * ((scl.y / 2.f) - scl.x);
	}

	Vector3 Capsule::GetBottomSpherePos() const
	{
		const auto scl = GetWorldScale();
		return GetWorldPos() + GetWorldRot().GetDown() * ((scl.y / 2.f) - scl.x);
	}

	std::vector<Vector3> Capsule::GetVertexes()
	{
		std::vector<Vector3> vertexes;

		const auto topPos = GetTopSpherePos();
		const auto bottomPos = GetBottomSpherePos();
		const auto scale = GetWorldScale();
		const auto rot = GetWorldRot();

		const auto up = rot.GetUp() * scale.y;
		const auto down = rot.GetDown() * scale.y;
		const auto left = rot.GetLeft() * scale.x;
		const auto right = rot.GetRight() * scale.x;
		const auto forward = rot.GetForward() * scale.z;
		const auto back = rot.GetBack() * scale.z;

		const auto fl = (forward + left).Normalized();
		const auto bl = (back + left).Normalized();
		const auto br = (back + right).Normalized();
		const auto fr = (forward + right).Normalized();

		vertexes.emplace_back(GetTop());

		vertexes.emplace_back(topPos + (forward + up).Normalized() * scale.x);
		vertexes.emplace_back(topPos + (fl+up).Normalized() * scale.x);
		vertexes.emplace_back(topPos + (left + up).Normalized()* scale.x);
		vertexes.emplace_back(topPos + (bl + up).Normalized() * scale.x);
		vertexes.emplace_back(topPos + (back + up).Normalized()* scale.x);
		vertexes.emplace_back(topPos + (br + up).Normalized()* scale.x);
		vertexes.emplace_back(topPos + (right + up).Normalized()* scale.x);
		vertexes.emplace_back(topPos + (fr + up).Normalized() * scale.x);

		vertexes.emplace_back(topPos + forward * scale.x);
		vertexes.emplace_back(topPos + fl * scale.x);
		vertexes.emplace_back(topPos + left * scale.x);
		vertexes.emplace_back(topPos + bl * scale.x);
		vertexes.emplace_back(topPos + back * scale.x);
		vertexes.emplace_back(topPos + br * scale.x);
		vertexes.emplace_back(topPos + right * scale.x);
		vertexes.emplace_back(topPos + fr * scale.x);
		
		vertexes.emplace_back(bottomPos + forward * scale.x);
		vertexes.emplace_back(bottomPos + fl * scale.x);
		vertexes.emplace_back(bottomPos + left * scale.x);
		vertexes.emplace_back(bottomPos + bl * scale.x);
		vertexes.emplace_back(bottomPos + back * scale.x);
		vertexes.emplace_back(bottomPos + br * scale.x);
		vertexes.emplace_back(bottomPos + right * scale.x);
		vertexes.emplace_back(bottomPos + fr * scale.x);

		vertexes.emplace_back(bottomPos + (forward + down).Normalized() * scale.x);
		vertexes.emplace_back(bottomPos + (fl + down).Normalized() * scale.x);
		vertexes.emplace_back(bottomPos + (left + down).Normalized() * scale.x);
		vertexes.emplace_back(bottomPos + (bl + down).Normalized() * scale.x);
		vertexes.emplace_back(bottomPos + (back + down).Normalized() * scale.x);
		vertexes.emplace_back(bottomPos + (br + down).Normalized() * scale.x);
		vertexes.emplace_back(bottomPos + (right + down).Normalized() * scale.x);
		vertexes.emplace_back(bottomPos + (fr + down).Normalized() * scale.x);

		vertexes.emplace_back(GetBottom());

		return vertexes;
	}

	std::vector<int> Capsule::GetVertexIndexes()
	{
		int div_2 = 8;
		auto max = div_2 * 4 + 2;
		std::vector<int> vertexIndexes;
		//天点とつながっている層
		for(int i = 1; i <= div_2; ++i)
		{
			if(i == div_2)
			{
				vertexIndexes.emplace_back(0);
				vertexIndexes.emplace_back(1);
				vertexIndexes.emplace_back(i);
			}
			else
			{
				vertexIndexes.emplace_back(0);
				vertexIndexes.emplace_back(i + 1);
				vertexIndexes.emplace_back(i);
			}
		}
		//天点と底点にくっついてない層
		for(int i = 0; i < 3; ++i)
		{
			for(int j = 1; j <= div_2; ++j)
			{
				auto p1 = j + (div_2 * i);
				auto p3 = p1 + div_2;
				if(j == div_2)
				{
					auto p2 = (p1 + 1) - div_2;
					auto p4 = (p3 + 1) - div_2;
					vertexIndexes.emplace_back(p1);
					vertexIndexes.emplace_back(p2);
					vertexIndexes.emplace_back(p3);

					vertexIndexes.emplace_back(p2);
					vertexIndexes.emplace_back(p4);
					vertexIndexes.emplace_back(p3);
				}
				else
				{
					auto p2 = p1 + 1;
					auto p4 = p2 + div_2;
					vertexIndexes.emplace_back(p1);
					vertexIndexes.emplace_back(p2);
					vertexIndexes.emplace_back(p3);

					vertexIndexes.emplace_back(p2);
					vertexIndexes.emplace_back(p4);
					vertexIndexes.emplace_back(p3);
				}
			}

		}
		//底点とつながっている層
		auto p1 = max - 1;
		for(int i = 0; i < div_2; ++i)
		{
			if(i == div_2-1)
			{
				vertexIndexes.emplace_back(p1);
				vertexIndexes.emplace_back((p1 - div_2) + i);
				vertexIndexes.emplace_back(((p1 - div_2) + i + 1)-div_2);
			}
			else
			{
				vertexIndexes.emplace_back(p1);
				vertexIndexes.emplace_back((p1 - div_2) + i);
				vertexIndexes.emplace_back((p1 - div_2) + i + 1);
			}
		}
		return vertexIndexes;
	}

	Mesh Capsule::GetMesh()
	{
		Mesh mesh(GetVertexes(),GetVertexIndexes());
		return mesh;
	}
}


