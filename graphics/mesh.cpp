#include "mesh.h"

Mesh::Mesh(const std::vector<Vertex1P1N1U>& vertices)
	: m_Vertices(vertices)
{
}

GLuint Mesh::GetSize() const
{
    return m_Vertices.size() * sizeof(Vertex1P1N1U);
}

const Vertex1P1N1U* Mesh::GetRaw() const
{
    return m_Vertices.data();
}

Vertex1P1N1U* Mesh::GetRaw()
{
    return m_Vertices.data();
}
