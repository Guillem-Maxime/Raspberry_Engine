#pragma once

#include "graphicsheader.h"

#include "vertex.h"

class Mesh
{
public:
	Mesh(const std::vector<Vertex1P1N1U>& vertices);

    GLuint GetSize() const;
    const Vertex1P1N1U* GetRaw() const;
    Vertex1P1N1U* GetRaw();
private:
	std::vector<Vertex1P1N1U> m_Vertices;
};
