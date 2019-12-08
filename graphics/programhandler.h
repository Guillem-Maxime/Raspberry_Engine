#pragma once

#include "graphicsheader.h"

#include "openglobjecthandler.h"
#include "shaderhandler.h"

class ProgramHandler : OpenGLObjectHandler
{
public:
	explicit ProgramHandler() = default;
	explicit ProgramHandler(const std::vector<ShaderHandler>& shaders);
	~ProgramHandler();

	void Init(const std::vector<ShaderHandler>& shaders);
	void LinkProgram() const;
	void UseProgram() const;

    template<class T>
    void SetUniformVariable(const T& myUniformVariable, const char* nameInShader) const; 
protected:
	virtual void GenerateGLObjectId() override;

private:
	GLuint m_ProgramId;

    void Uniform(GLint location, GLfloat myUniformVariable)  const;
    void Uniform(GLint location, GLint myUniformVariable) const;
    void Uniform(GLint location, GLuint myUniformVariable) const;
    void Uniform(GLint location, const glm::vec3& myUniformVariable) const;
    void Uniform(GLint location, const glm::vec4& myUniformVariable) const;
    void Uniform(GLint location, const glm::mat3& myUniformVariable) const;
    void Uniform(GLint location, const glm::mat4& myUniformVariable) const;
};

template<class T>
void ProgramHandler::SetUniformVariable(const T& myUniformVariable, const char* nameInShader) const
{
    GLint location{ glGetUniformLocation(m_ProgramId, nameInShader) };
    UseProgram();
    Uniform(location, myUniformVariable);
}
