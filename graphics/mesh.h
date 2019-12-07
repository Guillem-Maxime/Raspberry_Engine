#pragma once

#include "graphicsheader.h"

#include "vertex.h"

class Mesh
{
public:
	Mesh() = default;
	virtual ~Mesh() = default;

    GLuint GetSize() const;
    const Vertex1P1N1U* GetRaw() const;
    Vertex1P1N1U* GetRaw();
	inline void SetVertices(const std::vector<Vertex1P1N1U>& vertices) { m_Vertices = vertices; }
private:
	std::vector<Vertex1P1N1U> m_Vertices;
};
