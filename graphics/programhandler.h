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

protected:
	virtual void GenerateGLObjectId() override;

private:
	GLuint m_ProgramId;
};
