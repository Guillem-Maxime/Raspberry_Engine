#pragma once

#include "graphicsheader.h"

#include "vertex.h"

class Mesh
{
public:
	Mesh() = default;
	virtual ~Mesh() = default;

	Mesh& operator=(const Mesh& rhs) = default;
	Mesh(const Mesh& rhs) = default;

    GLuint GetNumberOfElements() const { return static_cast<GLuint>( m_Vertices.size() ); }
    const Vertex1P1N1U* GetRaw() const { return m_Vertices.data(); }
    Vertex1P1N1U* GetRaw() { return m_Vertices.data(); }
	GLuint GetSizeOf() const { return static_cast<GLuint>( m_Vertices.size() ) * sizeof(Vertex1P1N1U); }

	inline void SetVertices(const std::vector<Vertex1P1N1U>& vertices) { m_Vertices = vertices; }
	inline void SetIndices(const std::vector<GLuint>& indices) {m_Indices = indices; }
private:
	std::vector<Vertex1P1N1U> m_Vertices;
	std::vector<GLuint> m_Indices;
};
