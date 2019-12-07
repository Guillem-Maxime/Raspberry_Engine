#include "shaderhandler.h"

#include "utils/fileutils.h"

const std::string ShaderHandler::ms_ShaderDirectory = "shaders/";

ShaderHandler::ShaderHandler(const ShaderInfos& shaderInfos)
{
	Init(shaderInfos);
}

void ShaderHandler::Init(const ShaderInfos& infos)
{
	m_ShaderInfos = infos;
	if(IsValidShaderType())
	{
		InitInternal();
		GenerateGLObjectId();
		ReadShaderSource();
		const GLchar* shaderSource{m_ShaderSource.c_str()  };
		glShaderSource(m_ShaderId, 1, &shaderSource, nullptr);
		glCompileShader(m_ShaderId);
		CheckShaderCompilation();
	}
	else
	{
		std::cerr << "INVALID SHADER TYPE"  << std::endl;
	}
}

void ShaderHandler::GenerateGLObjectId()
{
	m_ShaderId = glCreateShader(m_ShaderInfos.shaderType);
}

ShaderHandler::~ShaderHandler()
{
	glDeleteShader(m_ShaderId);
}

void ShaderHandler::ReadShaderSource()
{
	const std::string shaderFileName = ShaderHandler::ms_ShaderDirectory + m_ShaderInfos.shaderName;
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
		std::cerr << "SHADER_NAME::"  << m_ShaderInfos.shaderName << std::endl;
		std::cerr << "SHADER::SOURCE::" << m_ShaderSource << std::endl;
	}
}

constexpr bool ShaderHandler::IsValidShaderType() const
{
	switch(m_ShaderInfos.shaderType)
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
	switch(m_ShaderInfos.shaderType)
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
