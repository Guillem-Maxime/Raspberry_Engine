#pragma once

#include "graphicsheader.h"

#include "bufferobjectbase.h"

struct EBOInfos
{
	std::vector<GLuint> m_Indices{};
	GLenum m_BufferUsage{ GL_DYNAMIC_DRAW };
	GLenum m_DrawMode{ GL_TRIANGLES };
};

class EBOHandler : public BufferObjectBase<EBOHandler>
{
public:
	void Draw() const;
	void Init(const EBOInfos& infos);

private:
	std::vector<GLuint> m_Indices{};
	GLenum m_BufferUsage;
	GLenum m_DrawMode;

	friend BufferObjectBase<EBOHandler>;

	inline GLenum GetBufferUsage() const { return m_BufferUsage; }
	inline const GLuint* GetBufferRawData() const { return m_Indices.data(); }
	inline GLuint GetBufferSizeOf() const { return sizeof(GLuint) * static_cast<GLuint>(m_Indices.size()); }
	inline GLenum GetBufferType() const { return GL_ELEMENT_ARRAY_BUFFER; }
	
	void PrepareInternal() const;
};
