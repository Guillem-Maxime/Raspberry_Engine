#include "graphics/mesh.h"

void Mesh::SetIndices(const std::vector<GLuint>& indices) 
{
   	m_Indices = indices; 
}

void Mesh::SetVAO(VAOHandler* value) 
{ 
	m_VAO = value; 
}

void Mesh::SetVertices(const std::vector<Vertex1P1N1U>& vertices) 
{ 
	m_Vertices = vertices; 
}

