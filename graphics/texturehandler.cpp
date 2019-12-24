#include "graphics/texturehandler.h"

#include "graphics/glutils.h"
#include "utils/fileutils.h"

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

void TextureHandler::Shutdown() const
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
	GLUtils::GetGLError("ApplyTexParameter_Wrap_S");
	glTexParameteri(m_TextureType, GL_TEXTURE_WRAP_T, static_cast<GLint>(m_TextureWrapType) );
	GLUtils::GetGLError("ApplyTexParameter_Wrap_T");
	glTexParameteri(m_TextureType, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(m_TextureFilteringType) );
	GLUtils::GetGLError("ApplyTexParameter_Min_Filter");
	glTexParameteri(m_TextureType, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(m_TextureFilteringType) );	
	GLUtils::GetGLError("ApplyTexParameter_Mag_Filter");
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//GLUtils::GetGLError("ApplyTexParameter_TexEnvi");
}

void TextureHandler::LoadAndGenerateTexture() const
{
	const char* filename{ m_File.c_str() };
	/*
	int width{0};
	int height{0};
	int nbrChannels{0};
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data{ stbi_load(filename, &width, &height, &nbrChannels, 0) };
	*/
	FileUtils::ImageInfos infos{};
	unsigned char* data{ FileUtils::LoadTexture(filename, infos) };
	if(data != nullptr)
	{
		glTexImage2D(m_TextureType, 0, static_cast<GLint>(infos.m_ColorChannel), infos.m_Width, infos.m_Height, 0, infos.m_ColorChannel, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(m_TextureType);
		GLUtils::GetGLError("LoadAndGenerateTexture");
	}
	else
	{
		std::cerr << "ERROR::LOADING::TEXTURE::FILE : " << m_File << std::endl;
	}
	//stbi_image_free(data);	
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
