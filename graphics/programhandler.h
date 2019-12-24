#pragma once

#include "graphicsheader.h"

#include "openglobjecthandler.h"
#include "shaderhandler.h"

class TextureHandler;

struct ProgramInitializer
{
	std::vector<ShaderInfos> m_ShaderInfos;
};

class ProgramHandler : OpenGLObjectHandler
{
public:
	explicit ProgramHandler() = default;
	~ProgramHandler() = default;

	void Init(const ProgramInitializer& init);
	void Shutdown();
	void Link();
	void Use() const;

	void AddTexture(TextureHandler* texture);

    template<class T>
    void SetUniformVariable(const T& myUniformVariable, const char* nameInShader) const; 
protected:
	virtual void GenerateGLObjectId() override;

private:
	std::vector<ShaderHandler> m_Shaders{};
	std::vector<TextureHandler*> m_Textures{};
	GLuint m_ProgramId{0};
	
	void CompileShaders() const;
	void DeleteShaders();

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
    Use();
    Uniform(location, myUniformVariable);
}
