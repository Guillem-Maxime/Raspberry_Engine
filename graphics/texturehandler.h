#pragma once

#include "graphicsheader.h"

#include "openglobjecthandler.h"

struct TextureInfos
{
	std::string m_TextureFile{""};
    GLenum m_TextureDimension{ GL_TEXTURE_2D };
	GLenum m_TextureWrapType{ GL_REPEAT };
	GLenum m_TextureFilteringType{ GL_LINEAR };
	GLenum m_TextureType;
};

class TextureHandler : public OpenGLObjectHandler
{
public:
	explicit TextureHandler() = default;
    
	void Init(const TextureInfos& infos);
	void Shutdown() const;
	void Prepare() const;

	inline const std::string& GetFile() const { return m_File;}
	inline void SetTextureFile(const std::string& value) { m_File = ms_TextureDirectory + value; }	
	inline void SetTextureDimension(GLenum value) { m_TextureDimension = value;}
	inline void SetAiTextureType(GLenum value) { m_AiTextureType = value;}
	inline void SetTextureWrapType(GLenum value) { m_TextureWrapType = value; }
	inline void SetTextureFilteringType(GLenum value) { m_TextureFilteringType = value; }
	inline GLint GetActiveTextureId() const { return m_ActiveTextureId;}

	void Bind() const;
	void Unbind() const;
	void UseTexture(GLint textureNbr);

protected:
	virtual void GenerateGLObjectId() override;

private:
	static const std::string ms_TextureDirectory;
	std::string m_File{""};
	GLuint m_TextureId{ 0 };
	GLint m_ActiveTextureId{ 0 };
	GLenum m_TextureDimension{ GL_NONE };
	GLenum m_AiTextureType{ GL_NONE };
	GLenum m_TextureWrapType{ GL_REPEAT };
	GLenum m_TextureFilteringType{ GL_LINEAR };

	void ApplyParameters() const;
	std::string GetTextureDimensionStr() const;
	void LoadAndGenerateTexture() const;
};
