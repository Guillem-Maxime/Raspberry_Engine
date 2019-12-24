#include "programhandler.h"

#include "glutils.h"
#include "texturehandler.h"

void ProgramHandler::Init(const ProgramInitializer& init)
{
	InitInternal();
	for(const auto& shaderInfos : init.m_ShaderInfos)
	{
		ShaderHandler shader;
		shader.Init(shaderInfos);
		m_Shaders.push_back(shader);
	}
}

void ProgramHandler::Shutdown()
{
	std::cerr << "deleting program : " << m_ProgramId << std::endl;
	glDeleteProgram(m_ProgramId);
}

void ProgramHandler::GenerateGLObjectId()
{
	m_ProgramId = glCreateProgram();
}

void ProgramHandler::Link()
{
	if(IsInitialized())
	{
		CompileShaders();
		glLinkProgram(m_ProgramId);
		GLUtils::GetGLError("glLinkProgram");
		DeleteShaders();
		int success;
		char infoLog[512];
		glGetProgramiv(m_ProgramId, GL_LINK_STATUS, &success);
		if(!success)
		{
			glGetProgramInfoLog(m_ProgramId, 512, nullptr, infoLog);
			std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
	}
	else
	{
		std::cerr << "ERROR::UNINITIALIZED::PROGRAM::LINK::" << m_ProgramId << std::endl;
	}
}

void ProgramHandler::Use() const
{
	if(IsInitialized())
	{
/*
		for(size_t i{0} ; i < m_Textures.size() ; i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			m_Textures[i]->Bind();
		}
*/
		glUseProgram(m_ProgramId);
		GLUtils::GetGLError("glUseProgram");
	}
	else
	{
		std::cerr << "ERROR::UNINITIALIZED::PROGRAM::USE::" << m_ProgramId << std::endl;
	}
}

void ProgramHandler::CompileShaders() const
{
	for(const auto& shader : m_Shaders)
	{
		shader.Compile();
		glAttachShader(m_ProgramId, shader.GetShaderId());
		GLUtils::GetGLError("glAttachShader");
	}
}

void ProgramHandler::AddTexture(TextureHandler* texture)
{
	m_Textures.push_back(texture);
	GLint textureId = static_cast<GLint>(m_Textures.size()) - 1;
	std::string textureName = "texture" + std::to_string(textureId);
	SetUniformVariable(textureId, textureName.c_str());
}

void ProgramHandler::DeleteShaders()
{
	for(const auto& shader : m_Shaders)
	{
		shader.Delete();
	}
	m_Shaders.clear();
}

void ProgramHandler::Uniform(const GLint location, const GLfloat myUniformVariable) const
{
    glUniform1f(location, myUniformVariable);
}

void ProgramHandler::Uniform(const GLint location, const GLint myUniformVariable) const
{
    glUniform1i(location, myUniformVariable);
}

void ProgramHandler::Uniform(const GLint location, const GLuint myUniformVariable) const
{
    glUniform1ui(location, myUniformVariable);
}

void ProgramHandler::Uniform(const GLint location, const glm::vec3& myUniformVariable) const
{
    glUniform1fv(location, 1, glm::value_ptr(myUniformVariable));
}

void ProgramHandler::Uniform(const GLint location, const glm::vec4& myUniformVariable) const
{
    glUniform1fv(location, 1, glm::value_ptr(myUniformVariable));
}

void ProgramHandler::Uniform(const GLint location, const glm::mat3& myUniformVariable) const
{
    glUniformMatrix3fv(location, 1, false, glm::value_ptr(myUniformVariable));
}

void ProgramHandler::Uniform(const GLint location, const glm::mat4& myUniformVariable) const
{
    glUniformMatrix4fv(location, 1, false, glm::value_ptr(myUniformVariable));
}

