#pragma once

#include "graphicsheader.h"

#include "shader.h"

class Program
{
public:
	Program(const std::vector<Shader>& shaders);
	~Program();

	void LinkProgram() const;
	void UseProgram() const;

private:
	GLuint m_ProgramId;
};
