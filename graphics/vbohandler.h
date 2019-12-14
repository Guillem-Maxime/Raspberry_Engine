#pragma once

#include "graphicsheader.h"
#include "mesh.h"
#include "openglobjecthandler.h"

struct VBOInitializer
{
	GLenum m_BufferType{GL_ARRAY_BUFFER};
	GLenum m_BufferUsage{GL_STATIC_DRAW};
	GLenum m_DrawMode{GL_TRIANGLES};
	Mesh m_Mesh;
};

class VBOHandler : public OpenGLObjectHandler
{
public:
	explicit VBOHandler() = default;
	virtual ~VBOHandler();
	
	void Init(const VBOInitializer& initializer);
	void Bind() const;
	void Unbind() const;
	void Compute() const;
	void Draw() const;

protected:
	virtual void GenerateGLObjectId() override;

private:
	std::vector<AttribPointerInfo> m_AttribPointerInfos;
    Mesh m_Mesh;
	GLuint m_BufferId{0};
	GLenum m_BufferType;
	GLenum m_BufferUsage;
	GLenum m_DrawMode;

	void AttribAndEnablePointer() const;	
	void BufferData() const;
	std::string GetBufferTypeStr() const;
};
