#pragma once

#include "graphicsheader.h"

#include "openglobjecthandler.h"

struct ShaderInfos
{
    std::string shaderName{""};
    GLenum shaderType{GL_NONE};
};

class ShaderHandler : public OpenGLObjectHandler
{
public:
	explicit ShaderHandler() = default;
	explicit ShaderHandler(const ShaderInfos& infos);
	virtual ~ShaderHandler();

	void Init(const ShaderInfos& infos);
	inline GLuint GetShaderId() const { return m_ShaderId; }

	static const std::string ms_ShaderDirectory;

protected:
	virtual void GenerateGLObjectId() override;

private:
	ShaderInfos m_ShaderInfos{""};
	GLuint m_ShaderId{0};
	std::string m_ShaderSource{};

	void ReadShaderSource();
	void CheckShaderCompilation() const;
	constexpr std::string_view GetShaderTypeString() const;
	constexpr bool IsValidShaderType() const;
};
