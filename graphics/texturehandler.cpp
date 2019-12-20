#include "texturehandler.h"

#include "glutils.h"

const std::string TextureHandler::ms_TextureDirectory = "textures/";

void TextureHandler::Init(const TextureInfos& infos)
{
	InitInternal();
	SetTextureFile(infos.m_TextureFile);
	SetTextureType(infos.m_TextureType);
	SetTextureWrapType(infos.m_TextureWrapType);
	SetTextureFilteringType(infos.m_TextureFilteringType);
}

void TextureHandler::Prepare() const
{
	Bind();
	ApplyParameters();
	LoadAndGenerateTexture();
}

void TextureHandler::Delete() const
{
	glDeleteTextures(1, &m_TextureId);
}

void TextureHandler::GenerateGLObjectId()
{
	glGenTextures(1, &m_TextureId);
}

void TextureHandler::Bind() const
{
	if(IsInitialized())
	{
		glBindTexture(m_TextureType, m_TextureId);
		if(GLUtils::GetGLError("TextureBind"))
		{
			std::cerr << "\tID::" << m_TextureId << "::" << GetTextureTypeStr() << std::endl;
		}
	}
	else
	{
		std::cerr << "ERROR::TEXTUREHANDLER::NOT_INITIALIZED : " << m_File << std::endl;
	}
}

void TextureHandler::Unbind() const
{
	glBindTexture(m_TextureType, 0);
	if(GLUtils::GetGLError("TextureUnbind"))
	{
		std::cerr << "\tID::" << m_TextureId << "::" << GetTextureTypeStr() << std::endl;
	}
}

void TextureHandler::ApplyParameters() const
{
	glTexParameteri(m_TextureType, GL_TEXTURE_WRAP_S, static_cast<GLint>(m_TextureWrapType) );
	glTexParameteri(m_TextureType, GL_TEXTURE_WRAP_T, static_cast<GLint>(m_TextureWrapType) );
	glTexParameteri(m_TextureType, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(m_TextureFilteringType) );
	glTexParameteri(m_TextureType, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(m_TextureFilteringType) );
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	GLUtils::GetGLError("ApplyParameters");
}

void TextureHandler::LoadAndGenerateTexture() const
{
	int width{0};
	int height{0};
	int nbrChannels{0};
	const char* filename{ m_File.c_str() };
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data{ stbi_load(filename, &width, &height, &nbrChannels, 0) };
	if(data != nullptr)
	{
		glTexImage2D(m_TextureType, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(m_TextureType);
		GLUtils::GetGLError("LoadAndGenerateTexture");
	}
	else
	{
		std::cerr << "ERROR::LOADING::TEXTURE::FILE : " << m_File << std::endl;
	}
	stbi_image_free(data);	
}

std::string TextureHandler::GetTextureTypeStr() const
{
	switch(m_TextureType)
	{
		case GL_TEXTURE_2D :
			return "GL_TEXTURE_2D";
		default:
			return "OTHER::ENUM";
	}
}
