#include "vbohandler.h"

VBOHandler::VBOHandler(const VBOInitializer& initializer)
	: m_BufferType(initializer.m_BufferType)
	, m_BufferUsage(initializer.m_BufferUsage)
{
	glGenBuffers(1, &m_BufferId);
}

VBOHandler::~VBOHandler()
{

}

void VBOHandler::ComputeBuffer() const
{
	BindBuffer();
	BufferData();
	AttribAndEnablePointer();
}

void VBOHandler::BindBuffer() const
{
	glBindBuffer(m_BufferType, m_BufferId);
}

void VBOHandler::BufferData() const
{
	glBufferData(m_BufferType, m_Mesh.GetSize(), m_Mesh.GetRaw(), m_BufferUsage);
}

void VBOHandler::AttribAndEnablePointer() const
{
	m_Mesh.AttribAndEnablePointer();
}
