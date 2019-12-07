#include "vbohandler.h"

VBOHandler::VBOHandler(const VBOInitializer& initializer)
	: m_BufferType(initializer.m_BufferType)
	, m_BufferUsage(initializer.m_BufferUsage)
	, m_DrawMode(initializer.m_DrawMode)
	, m_Mesh(initializer.m_Mesh)
{
	glGenBuffers(1, &m_BufferId);
}

VBOHandler::~VBOHandler()
{
	glDeleteBuffers(1, &m_BufferId);
}

void VBOHandler::Compute() const
{
	Bind();
	BufferData();
	AttribAndEnablePointer();
}

void VBOHandler::Bind() const
{
	glBindBuffer(m_BufferType, m_BufferId);
}

void VBOHandler::BufferData() const
{
	glBufferData(m_BufferType, m_Mesh.GetSize(), m_Mesh.GetRaw(), m_BufferUsage);
}

void VBOHandler::AttribAndEnablePointer() const
{
    std::vector<AttribPointerInfo> infos;
	Vertex1P1N1U::GetAttribPointerInfo(infos);
    for(const auto& info : infos)
    {
        glVertexAttribPointer(info.m_Position, info.m_Size, GL_FLOAT, GL_FALSE, info.m_Stride, (void*)info.m_Offset);
        glEnableVertexAttribArray(info.m_Position);
	}	
}

void VBOHandler::Unbind() const
{
	glBindBuffer(m_BufferType, 0);
}

void VBOHandler::Draw() const
{
	Bind();
	glDrawArrays(m_DrawMode, 0, 3);
	Unbind();
}
