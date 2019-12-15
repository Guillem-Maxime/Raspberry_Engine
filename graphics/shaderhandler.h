#pragma once

#include "graphicsheader.h"

#include "openglobjecthandler.h"

struct ShaderInfos
{
    std::string m_ShaderName{""};
    GLenum m_ShaderType{GL_NONE};
};

class ShaderHandler : public OpenGLObjectHandler
{
public:
	explicit ShaderHandler() = default;
	virtual ~ShaderHandler() = default;

	void Init(const ShaderInfos& init);
	void Delete() const;

	void Compile() const;
	inline GLuint GetShaderId() const { return m_ShaderId; }

protected:
	virtual void GenerateGLObjectId() override;

private:
	static const std::string ms_ShaderDirectory;
	std::string m_ShaderName{""};
	std::string m_ShaderSource{""};
	GLenum m_ShaderType{GL_NONE};
	GLuint m_ShaderId{0};

	void ReadShaderSource();
	void CheckShaderCompilation() const;
	constexpr std::string_view GetShaderTypeString() const;
	constexpr bool IsValidShaderType() const;
};
