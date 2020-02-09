#pragma once

#include "graphics/vertex.h"
#include "graphics/texturehandler.h"

class VAOHandler;

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

	void SetIndices(const std::vector<GLuint>& indices);
	void SetTextures(const std::vector<TextureHandler>& textures);
	void SetVAO(VAOHandler* value);
	void SetVertices(const std::vector<Vertex1P1N1U>& vertices);

	void RegisterPosition(glm::mat4* position);
	void UnregisterPosition(glm::mat4* position);
private:
	std::vector<Vertex1P1N1U> m_Vertices{};
	std::vector<GLuint> m_Indices{};
	std::vector<TextureHandler> m_Textures{};
	VAOHandler* m_VAO;
};
