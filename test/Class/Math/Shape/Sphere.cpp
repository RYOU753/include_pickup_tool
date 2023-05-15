#include "../MathDefinition.h"
#include "../MathHelper.h"
#include "Sphere.h"

namespace Kirara::Math
{
	Sphere::Sphere(const Vector3& pos,const float& radius)
	{
		transform_.SetLocalPosition(pos);
		transform_.SetLocalScale(VECTOR3_ONE<>*radius);
	}

	Sphere::Sphere(const Transform& transform)
	{
		transform_ = transform;
	}

	Sphere::Sphere(const float& radius)
	{
		transform_.SetLocalPosition(VECTOR3_ZERO<>);
		transform_.SetLocalScale(VECTOR3_ONE<>*radius);
	}

	float Sphere::GetRadius(void) const
	{
		return transform_.GetWorldScale().x;
	}

	void Sphere::SetRadius(const float& radius)
	{
		transform_.SetLocalScale(VECTOR3_ONE<>*radius);
	}

	std::vector<Vector3> Sphere::GetVertexes()
	{
		constexpr int div = 5;
		std::vector<Vector3> vertexes;
		vertexes.reserve((div *2)* (div - 1)+2);
		auto topVertex = transform_.GetUp()* GetWorldScale();
		auto bottomVertex = transform_.GetDown()* GetWorldScale();
		vertexes.emplace_back(topVertex);
		for(auto i = 1;i < div;i ++)
		{
			vertexes.emplace_back(AngleAxis(i * DegToRad(180. / div), transform_.GetRight()).Multiply(GetWorldRot()).PosAxis(topVertex));
			
			const auto p = vertexes.back();
			for(auto j = 1;j<div*2;j++)
			{
				vertexes.emplace_back(AngleAxis(j * DegToRad(180. / div), DIR_UP<>).Multiply(GetWorldRot()).PosAxis(p));
			}
		}
		vertexes.emplace_back(bottomVertex);

		return vertexes;
	}

	std::vector<int> Sphere::GetVertexIndexes()
	{
		std::vector<int> vertexIndexes;
		//天点とつながっている層
		for (int i = 1; i <= 10; ++i)
		{
			if(i==10)
			{
				vertexIndexes.emplace_back(0);
				vertexIndexes.emplace_back(i);
				vertexIndexes.emplace_back(1);
			}else
			{
				vertexIndexes.emplace_back(0);
				vertexIndexes.emplace_back(i);
				vertexIndexes.emplace_back(i + 1);
			}
		}
		//天点と底点にくっついてない層
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 1; j <= 10; ++j)
			{
				if(j==10)
				{
					vertexIndexes.emplace_back(j + (10 * i));
					vertexIndexes.emplace_back((10 * (i + 1)) + j);
					vertexIndexes.emplace_back(j + (10 * i) + 1);

					vertexIndexes.emplace_back(j + (10 * i));
					vertexIndexes.emplace_back(j + (10 * i) + 1);
					vertexIndexes.emplace_back(j + (10 * i) + 1 - j);
				}else
				{
					vertexIndexes.emplace_back(j + (10 * i));
					vertexIndexes.emplace_back((10 * (i + 1)) + j);
					vertexIndexes.emplace_back((10 * (i + 1)) + j + 1);

					vertexIndexes.emplace_back(j + (10 * i));
					vertexIndexes.emplace_back((10 * (i + 1)) + j + 1);
					vertexIndexes.emplace_back(j + (10 * i) + 1);
				}
			}
			
		}
		//底点とつながっている層
		constexpr int div = 5;
		auto max = (div * 2)* (div - 1) + 2;
		for(int i = 0; i < 10; ++i)
		{
			if(i == 9)
			{
				vertexIndexes.emplace_back(max - 1);
				vertexIndexes.emplace_back(((max - 1) - div * 2));
				vertexIndexes.emplace_back(((max - 1) - div * 2) + i);
			}else
			{
				vertexIndexes.emplace_back(max - 1);
				vertexIndexes.emplace_back(((max - 1) - div * 2) + i+1);
				vertexIndexes.emplace_back(((max - 1) - div * 2) + i);
			}
		}

		return vertexIndexes;
	}

	Mesh Sphere::GetMesh()
	{
		Mesh mesh(GetVertexes(),GetVertexIndexes());
		return mesh;
	}
}

