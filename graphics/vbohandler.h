#pragma once

#include "graphicsheader.h"
#include "mesh.h"

struct VBOInitializer
{
	GLenum m_BufferType{GL_ARRAY_BUFFER};
	GLenum m_BufferUsage{GL_STATIC_DRAW};
	Mesh m_Mesh;
};

class VBOHandler
{
public:
	VBOHandler(const VBOInitializer& initializer);
	virtual ~VBOHandler();

	void ComputeBuffer() const;
	void BindBuffer() const;
	void BufferData() const;
	void AttribPointer() const;

private:
	const GLenum m_BufferType;
	GLenum m_BufferUsage;
	Mesh m_Mesh;
};
