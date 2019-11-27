#pragma once

#include "graphicsheader.h"

struct ShaderInfos
{
    const std::string shaderName{""};
    GLenum shaderType{GL_NONE};
};

class Shader
{
public:
	Shader(const ShaderInfos& infos);
	virtual ~Shader();

	inline GLuint GetShaderId() const { return m_ShaderId; }

	static const std::string ms_ShaderDirectory;

private:
	ShaderInfos m_ShaderInfos{""};
	GLuint m_ShaderId{0};
	std::string m_ShaderSource{};

	void ReadShaderSource();
	void CheckShaderCompilation() const;
	constexpr std::string_view GetShaderTypeString() const;
	constexpr bool IsValidShaderType() const;
};
