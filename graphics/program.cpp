#include "program.h"

#include <iostream>

Program::Program(const std::vector<Shader>& shaders)
	: m_ProgramId(0)
{
	m_ProgramId = glCreateProgram();
	for(const Shader& shader : shaders)
	{
		glAttachShader(m_ProgramId, shader.GetShaderId());
	}
	LinkProgram();

}

Program::~Program()
{
	glDeleteProgram(m_ProgramId);
}

void Program::LinkProgram() const
{
	glLinkProgram(m_ProgramId);
	int success;
	char infoLog[512];
	glGetProgramiv(m_ProgramId, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(m_ProgramId, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}

void Program::UseProgram() const
{
	glUseProgram(m_ProgramId);
}
