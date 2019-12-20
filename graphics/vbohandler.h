#pragma once

#include "graphicsheader.h"

#include "bufferobjectbase.h"
#include "mesh.h"
#include "openglobjecthandler.h"

struct VBOInfos
{
	Mesh m_Mesh;
	GLenum m_BufferUsage{GL_DYNAMIC_DRAW};
};

class VBOHandler : public BufferObjectBase<VBOHandler>
{
public:	
	void Init(const VBOInfos& infos);

private:
    Mesh m_Mesh;
	std::vector<AttribPointerInfo> m_AttribPointerInfos;
	GLenum m_BufferUsage;

	friend BufferObjectBase<VBOHandler>;

	void AttribAndEnablePointer() const;
	inline const Vertex1P1N1U* GetBufferRawData() const { return m_Mesh.GetRaw(); }
	inline GLuint GetBufferSizeOf() const { return m_Mesh.GetSizeOf(); }
	inline GLenum GetBufferType() const { return GL_ARRAY_BUFFER; }
	inline GLenum GetBufferUsage() const { return m_BufferUsage; }
	void PrepareInternal() const;
};
