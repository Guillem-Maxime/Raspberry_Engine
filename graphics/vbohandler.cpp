#include "vbohandler.h"

#include "glutils.h"

void VBOHandler::Init(const VBOInfos& infos)
{
	InitInternal();
	m_Mesh = infos.m_Mesh;
	m_BufferUsage = infos.m_BufferUsage;
	Vertex1P1N1U::GetAttribPointerInfos(m_AttribPointerInfos);
}

void VBOHandler::AttribAndEnablePointer() const
{
    for(const auto& info : m_AttribPointerInfos)
    {
		glVertexAttribPointer(info.m_Position, info.m_Size, GL_FLOAT, GL_FALSE, info.m_Stride, (void*)info.m_Offset);
		PrintErrorMessage("AttribPointer");
		glEnableVertexAttribArray(info.m_Position);
		PrintErrorMessage("EnableVertexAttribArray");
	}
}

void VBOHandler::PrepareInternal() const
{
	BufferData();
	AttribAndEnablePointer();
}
