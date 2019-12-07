#pragma once

#include "graphicsheader.h"

#include "openglobjecthandler.h"

class TextureHandler : public OpenGLObjectHandler
{
public:
	
protected:
	virtual void GenerateGLObjectId() override;

private:
	GLuint m_TextureId{0};

};
