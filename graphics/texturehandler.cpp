#include "texturehandler.h"

void TextureHandler::GenerateGLObjectId()
{
	glGenTextures(1, &m_TextureId);
}
