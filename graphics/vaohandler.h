#pragma once

#include "graphicsheader.h"

#include "programhandler.h"
#include "openglobjecthandler.h"
#include "texturehandler.h"
#include "vbohandler.h"

struct VAOInfos
{
	ProgramHandler m_Program;
	TextureHandler m_Texture;
};

class VAOHandler : public OpenGLObjectHandler
{
public:
	explicit VAOHandler() = default;
	virtual ~VAOHandler();

	void Init(const VAOInfos& infos);
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
	TextureHandler m_Texture;
	VBOHandler m_VBO;
};
