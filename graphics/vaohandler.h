#pragma once

#include "graphicsheader.h"

#include "programhandler.h"
#include "openglobjecthandler.h"
#include "vbohandler.h"

class VAOHandler : public OpenGLObjectHandler
{
public:
	explicit VAOHandler() = default;
	explicit VAOHandler(const ProgramHandler& program);
	virtual ~VAOHandler();

	void Init(const ProgramHandler& program);
	void Bind() const;
	void Unbind() const;
	void Compute() const;
	void Draw() const;
	void SetVBO(const VBOHandler& vbo);

protected:
	virtual void GenerateGLObjectId() override;

private:
	GLuint m_VAOId{0};
	ProgramHandler m_Program;
	VBOHandler m_VBO;
};
