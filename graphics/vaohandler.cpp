#include "vaohandler.h"

#include "glutils.h"

void VAOHandler::Init(const VAOInfos& infos)
{
	InitInternal();
	m_Program = infos.m_Program;
	m_Texture = infos.m_Texture;
}

void VAOHandler::GenerateGLObjectId()
{
	glGenVertexArrays(1, &m_VAOId); 
}

VAOHandler::~VAOHandler()
{
	glDeleteVertexArrays(1, &m_VAOId);
}

void VAOHandler::Bind() const
{
	if(IsInitialized())
	{
		glBindVertexArray(m_VAOId);
		if(GLUtils::GetGLError("VAOBind"))
		{
			std::cerr << "\tID::" << m_VAOId << std::endl;
		}
	}
	else
	{
		std::cerr << "VAO Not Initialized ID : " << m_VAOId << std::endl;
	}
}

void VAOHandler::Unbind() const
{
	glBindVertexArray(0);
	if(GLUtils::GetGLError("VAOBind"))
	{
		std::cerr << "\tID::" << m_VAOId << std::endl;
	}
}

void VAOHandler::Compute() const
{
	m_Program.UseProgram();
	m_VBO.Compute();
	m_Texture.Reset();
	m_Texture.UseTexture(0);
}

void VAOHandler::Draw() const
{
	m_Texture.UseTexture(0);
	GLUtils::GetGLError("Draw_UseTexture");
	m_Program.UseProgram();
	GLUtils::GetGLError("Draw_UseProgram");
	Bind();
	GLUtils::GetGLError("Draw_Bind");
	m_VBO.Draw();
	GLUtils::GetGLError("Draw_VBO");
}

void VAOHandler::SetVBO(const VBOHandler& vbo)
{
	m_VBO = vbo;
}
