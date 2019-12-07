#include "vbohandler.h"

VBOHandler::VBOHandler(const VBOInitializer& initializer)
{
	Init(initializer);
}

void VBOHandler::Init(const VBOInitializer& initializer)
{
	m_IsInitialized = true;
	m_Mesh = initializer.m_Mesh;
	m_BufferType = initializer.m_BufferType;
	m_BufferUsage = initializer.m_BufferUsage;
	m_DrawMode = initializer.m_DrawMode;
	glGenBuffers(1, &m_BufferId);
	Vertex1P1N1U::GetAttribPointerInfos(m_AttribPointerInfos);
}

VBOHandler::~VBOHandler()
{
	glDeleteBuffers(1, &m_BufferId);
}

void VBOHandler::Compute() const
{
	Bind();
	if(m_IsInitialized)
	{
		BufferData();
		AttribAndEnablePointer();
	}
	else
	{
		std::cout << "[ERROR] VBO ID : " << m_BufferId << " IS NOT INITIALIZED" << std::endl;
	}
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
    for(const auto& info : m_AttribPointerInfos)
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
