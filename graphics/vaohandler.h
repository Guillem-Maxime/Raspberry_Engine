#pragma once

#include "graphicsheader.h"

#include "program.h"
#include "vbohandler.h"

class VAOHandler
{
public:
	VAOHandler();
	virtual ~VAOHandler();

private:
	GLuint m_VAOId{0};
	std::vector<Shader> m_Shaders{};
	std::vector<Program> m_Programs{};
	std::vector<VBOHandler> m_VBOs{};
};
