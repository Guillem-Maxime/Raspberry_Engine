#pragma once

#include "graphicsheader.h"

#include "program.h"
#include "vbohandler.h"

class VAOHandler
{
public:
	explicit VAOHandler(const Program& program);
	virtual ~VAOHandler();

	void Bind() const;
	void Unbind() const;
	void Compute() const;
	void Draw() const;
	void SetVBO(const VBOHandler& vbo);
private:
	GLuint m_VAOId{0};
	Program m_Program;
	VBOHandler m_VBO;
};
