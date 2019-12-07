#pragma once

#include "graphicsheader.h"
#include "mesh.h"

struct VBOInitializer
{
	GLenum m_BufferType{GL_ARRAY_BUFFER};
	GLenum m_BufferUsage{GL_STATIC_DRAW};
	GLenum m_DrawMode{GL_TRIANGLES};
	Mesh m_Mesh;

	VBOInitializer(const Mesh& mesh) : m_Mesh(mesh) {}
	VBOInitializer(const GLenum bufferType, const GLenum bufferUsage, const Mesh& mesh) : m_BufferType(bufferType), m_BufferUsage(bufferUsage), m_Mesh(mesh) {}
};

class VBOHandler
{
public:
	VBOHandler(const VBOInitializer& initializer);
	virtual ~VBOHandler();

	void Bind() const;
	void Unbind() const;
	void Compute() const;
	void Draw() const;

private:
	const GLenum m_BufferType;
	GLenum m_BufferUsage;
	GLenum m_DrawMode;
	GLuint m_BufferId{0};
    Mesh m_Mesh;
	
	void BufferData() const;
	void AttribAndEnablePointer() const;
};
