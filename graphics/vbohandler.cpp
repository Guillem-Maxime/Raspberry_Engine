#include "vbohandler.h"

#include "glutils.h"

void VBOHandler::Init(const VBOInfos& infos)
{
	InitInternal();
	m_Mesh = infos.m_Mesh;
	m_BufferType = infos.m_BufferType;
	m_BufferUsage = infos.m_BufferUsage;
	m_DrawMode = infos.m_DrawMode;
	Vertex1P1N1U::GetAttribPointerInfos(m_AttribPointerInfos);
}

void VBOHandler::Delete() const
{
	std::cout << "Deleting Buffer : " << GetBufferTypeStr() << " : " << m_BufferId << std::endl;
	glDeleteBuffers(1, &m_BufferId);
}

void VBOHandler::GenerateGLObjectId()
{
	glGenBuffers(1, &m_BufferId);
	GLUtils::GetGLError("VBOGenBuffer");
}

void VBOHandler::Prepare() const
{
	Bind();
	if(IsInitialized())
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
	if(IsInitialized())
	{
		glBindBuffer(m_BufferType, m_BufferId);
		if(GLUtils::GetGLError("VBOBind"))
		{
			std::cerr << "\tID::" << m_BufferId << "::BUFFERTYPE::" << GetBufferTypeStr() << std::endl;
		}
	}
	else
	{
		std::cerr << "VBO Is Not Initialized ID : " << m_BufferId << std::endl;
	}
}

void VBOHandler::BufferData() const
{
	glBufferData(m_BufferType, m_Mesh.GetSizeOf(), m_Mesh.GetRaw(), m_BufferUsage);
	GLUtils::GetGLError("BufferData");
}

void VBOHandler::AttribAndEnablePointer() const
{
    for(const auto& info : m_AttribPointerInfos)
    {
		glVertexAttribPointer(info.m_Position, info.m_Size, GL_FLOAT, GL_FALSE, info.m_Stride, (void*)info.m_Offset);
		GLUtils::GetGLError("VertexAttribPointer");
		glEnableVertexAttribArray(info.m_Position);
		GLUtils::GetGLError("EnableVertexAttribArray");
	}
}

void VBOHandler::Unbind() const
{
	glBindBuffer(m_BufferType, 0);
	if(GLUtils::GetGLError("VBOUnbind"))
	{
		std::cerr << "\tID::" << m_BufferId << std::endl;
	}
}

void VBOHandler::Draw() const
{
	glDrawArrays(m_DrawMode, 0, m_Mesh.GetNumberOfElements());
	GLUtils::GetGLError("VBODraw_Draw");
}

std::string VBOHandler::GetBufferTypeStr() const
{
	switch(m_BufferType)
	{
		case GL_ARRAY_BUFFER:
			return "ARRAY_BUFFER";
		case GL_ELEMENT_ARRAY_BUFFER:
			return "ELEMENT_ARRAY_BUFFER";
		default:
			return "UNKNOWN_ENUM";
	}
}
