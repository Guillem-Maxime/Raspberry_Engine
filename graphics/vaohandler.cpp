#include "vaohandler.h"

VAOHandler::VAOHandler(const Program& program)
	: m_Program(program)
{
	glGenVertexArrays(1, &m_VAOId);
}

VAOHandler::~VAOHandler()
{
	glDeleteVertexArrays(1, &m_VAOId);
}

void VAOHandler::Bind() const
{
	glBindVertexArray(m_VAOId);
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
