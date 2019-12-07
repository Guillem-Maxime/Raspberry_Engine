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
	for(const auto& vbo : m_VBOs)
	{
		vbo.Compute();
	}
}

void VAOHandler::Draw() const
{
	Bind();
	for(const auto& vbo : m_VBOs)
	{
		vbo.Draw();
	}
}

void VAOHandler::AddVBO(VBOHandler& vbo)
{
	m_VBOs.push_back(vbo);
}
