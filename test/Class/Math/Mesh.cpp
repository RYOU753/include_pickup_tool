#include "Mesh.h"

namespace Kirara::Math
{
	Mesh::Mesh() = default;

	Mesh::Mesh(VertexesType vertexes, VertexIndexesType vertexIndexes)
		:vertexes(std::move(vertexes)),vertexIndexes(std::move(vertexIndexes))
	{
	}

	Mesh::~Mesh() = default;
}
