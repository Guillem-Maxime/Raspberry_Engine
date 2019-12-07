#include "programhandler.h"

#include <iostream>

ProgramHandler::ProgramHandler(const std::vector<ShaderHandler>& shaders)
{
	Init(shaders);
}

void ProgramHandler::Init(const std::vector<ShaderHandler>& shaders)
{
	InitInternal();
	for(const auto& shader : shaders)
	{
		glAttachShader(m_ProgramId, shader.GetShaderId());
	}
	LinkProgram();
}

void ProgramHandler::GenerateGLObjectId()
{
	m_ProgramId = glCreateProgram();
}

ProgramHandler::~ProgramHandler()
{
	glDeleteProgram(m_ProgramId);
}

void ProgramHandler::LinkProgram() const
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

void ProgramHandler::UseProgram() const
{
	if(IsInitialized())
	{
		glUseProgram(m_ProgramId);
	}
	else
	{
		std::cerr << "Program Not Initialized ID : " << m_ProgramId << std::endl;
	}
}
