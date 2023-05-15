#pragma once
#include <vector>

#include "Vector3.h"
namespace Kirara::Math
{
	class Mesh
	{
	public:
		using VertexesType = std::vector<Vector3>;
		using VertexIndexesType = std::vector<int>;

		Mesh();
		Mesh(VertexesType vertexes, VertexIndexesType vertexIndexes);
		~Mesh();
		VertexesType vertexes;
		VertexIndexesType vertexIndexes;
	private:
		
	};
}
