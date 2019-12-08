#pragma once

#include "graphicsheader.h"

#include "openglobjecthandler.h"

struct TextureInfos
{
    
};

class TextureHandler : public OpenGLObjectHandler
{
public:
	explicit TextureHandler() = default;
    


protected:
	virtual void GenerateGLObjectId() override;

private:
	GLuint m_TextureId{0};
};
