#include "graphics/mesh.h"

#include "graphics/vaohandler.h"

void Mesh::SetVAO(VAOHandler* value) 
{ 
	m_VAO = value; 
}

void Mesh::SetVertices(const std::vector<Vertex1P1N1U>& vertices) 
{ 
	m_Vertices = vertices; 
}

void Mesh::RegisterPosition(glm::mat4* position)
{
	if(m_VAO != nullptr)
	{
		m_VAO->RegisterPosition(position);
	}
	else
	{
		std::cerr << "ERROR::VAO_NULLPTR_IN_MESH" << std::endl;
	}
}

void Mesh::UnregisterPosition(glm::mat4* position)
{
	if(m_VAO != nullptr)
	{
		m_VAO->UnregisterPosition(position);
	}
}
