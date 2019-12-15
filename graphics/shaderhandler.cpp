#include "shaderhandler.h"

#include "utils/fileutils.h"

const std::string ShaderHandler::ms_ShaderDirectory = "shaders/";

void ShaderHandler::Init(const ShaderInfos& infos)
{
	m_ShaderType = infos.m_ShaderType;
	if(IsValidShaderType())
	{
		InitInternal();
		m_ShaderName = infos.m_ShaderName;
		GenerateGLObjectId();
		ReadShaderSource();
	}
	else
	{
		std::cerr << "INVALID SHADER TYPE"  << std::endl;
	}
}

void ShaderHandler::Delete() const
{
	glDeleteShader(m_ShaderId);
}

void ShaderHandler::Compile() const
{
	const GLchar* shaderSource{m_ShaderSource.c_str() };
	glShaderSource(m_ShaderId, 1, &shaderSource, nullptr);
	glCompileShader(m_ShaderId);
	CheckShaderCompilation();
}

void ShaderHandler::GenerateGLObjectId()
{
	m_ShaderId = glCreateShader(m_ShaderType);
}

void ShaderHandler::ReadShaderSource()
{
	const std::string shaderFileName = ShaderHandler::ms_ShaderDirectory + m_ShaderName;
	FileUtils::ReadFile(shaderFileName, m_ShaderSource);
}

void ShaderHandler::CheckShaderCompilation() const
{
	int success{0};
	glGetShaderiv(m_ShaderId, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(m_ShaderId, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::" << GetShaderTypeString()  << "::COMPILATION::FAILED\n" << infoLog; 
		std::cerr << "SHADER_ID::" << m_ShaderId << std::endl;
		std::cerr << "SHADER_NAME::"  << m_ShaderName << std::endl;
		std::cerr << "SHADER::SOURCE::" << m_ShaderSource << std::endl;
	}
	else
	{
		std::cerr << "SUCCESS::SHADER::" << GetShaderTypeString() << "::COMPILATION::" << m_ShaderName << std::endl;
	}
}

constexpr bool ShaderHandler::IsValidShaderType() const
{
	switch(m_ShaderType)
	{
	case GL_COMPUTE_SHADER:
	case GL_VERTEX_SHADER:
	case GL_TESS_CONTROL_SHADER:
	case GL_TESS_EVALUATION_SHADER:
	case GL_GEOMETRY_SHADER:
	case GL_FRAGMENT_SHADER:
		return true;
	default:
		return false;
	}
}

constexpr std::string_view ShaderHandler::GetShaderTypeString() const
{
	switch(m_ShaderType)
	{
	case GL_COMPUTE_SHADER:
		return "COMPUTE";
	case GL_VERTEX_SHADER:
		return "VERTEX";
	case GL_TESS_CONTROL_SHADER:
		return "TESS_CONTROL";
	case GL_TESS_EVALUATION_SHADER:
		return "TESS_EVALUATION";
	case GL_GEOMETRY_SHADER:
		return "GEOMETRY";
	case GL_FRAGMENT_SHADER:
		return "FRAGMENT";
	default:
		return "NONE";
	}
}
