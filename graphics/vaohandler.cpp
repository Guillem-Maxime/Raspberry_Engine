#include "vaohandler.h"

VAOHandler::VAOHandler(const ProgramHandler& program)
{
	Init(program);
}

void VAOHandler::Init(const ProgramHandler& program)
{
	InitInternal();
	m_Program = program;
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
	}
	else
	{
		std::cerr << "VAO Not Initialized ID : " << m_VAOId << std::endl;
	}
}

void VAOHandler::Unbind() const
{
	glBindVertexArray(0);
}

void VAOHandler::Compute() const
{
	m_Program.UseProgram();
	m_VBO.Compute();
}

void VAOHandler::Draw() const
{
	Bind();
	m_VBO.Draw();
	Unbind();
}

void VAOHandler::SetVBO(const VBOHandler& vbo)
{
	m_VBO = vbo;
}
