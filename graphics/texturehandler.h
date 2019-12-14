#pragma once

#include "graphicsheader.h"

#include "openglobjecthandler.h"

struct TextureInfos
{
	std::string m_TextureFile{""};
    GLenum m_TextureType{ GL_TEXTURE_2D };
	GLenum m_TextureWrapType{ GL_REPEAT };
	GLenum m_TextureFilteringType{ GL_LINEAR };
};

class TextureHandler : public OpenGLObjectHandler
{
public:
	explicit TextureHandler() = default;
    
	void Init(const TextureInfos& infos);
	void Reset() const;

	inline void SetTextureFile(const std::string& value) { m_File = ms_TextureDirectory + value; }
	inline void SetTextureType(GLenum value) { m_TextureType = value;}
	inline void SetTextureWrapType(GLenum value) { m_TextureWrapType = value; }
	inline void SetTextureFilteringType(GLenum value) { m_TextureFilteringType = value; }

	void Bind() const;
	void Unbind() const;
	void UseTexture(GLuint textureNbr) const;

protected:
	virtual void GenerateGLObjectId() override;

private:
	static const std::string ms_TextureDirectory;
	std::string m_File{""};
	GLuint m_TextureId{ 0 };
	GLenum m_TextureType{ GL_NONE };
	GLenum m_TextureWrapType{ GL_REPEAT };
	GLenum m_TextureFilteringType{ GL_LINEAR };

	void ApplyParameters() const;
	std::string GetTextureTypeStr() const;
	void LoadAndGenerateTexture() const;
};
