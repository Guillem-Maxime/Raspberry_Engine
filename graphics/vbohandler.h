#pragma once

#include "graphicsheader.h"
#include "mesh.h"
#include "openglobjecthandler.h"

struct VBOInfos
{
	Mesh m_Mesh;
	GLenum m_BufferType{GL_ARRAY_BUFFER};
	GLenum m_BufferUsage{GL_STATIC_DRAW};
	GLenum m_DrawMode{GL_TRIANGLES};
};

class VBOHandler : public OpenGLObjectHandler
{
public:
	explicit VBOHandler() = default;
	virtual ~VBOHandler() = default;
	
	void Init(const VBOInfos& infos);
	void Delete() const;
	void Bind() const;
	void Unbind() const;
	void Prepare() const;
	void Draw() const;

protected:
	virtual void GenerateGLObjectId() override;

private:
    Mesh m_Mesh;
	std::vector<AttribPointerInfo> m_AttribPointerInfos;
	GLuint m_BufferId{0};
	GLenum m_BufferType;
	GLenum m_BufferUsage;
	GLenum m_DrawMode;

	void AttribAndEnablePointer() const;	
	void BufferData() const;
	std::string GetBufferTypeStr() const;
};
