#pragma once

#include "graphicsheader.h"

#include "ebohandler.h"
#include "programhandler.h"
#include "openglobjecthandler.h"
#include "texturehandler.h"
#include "vbohandler.h"

class Camera;

struct VAOInitializer
{
	EBOInfos m_EBOInfos;
	ProgramInitializer m_ProgramInitializer;
	TextureInfos m_TextureInfos;
	VBOInfos m_VBOInfos;
	Camera* m_Camera{nullptr};
};

class VAOHandler : public OpenGLObjectHandler
{
public:
	explicit VAOHandler() = default;
	virtual ~VAOHandler() = default;

	void Init(const VAOInitializer& initializer);
	void Delete();
	void Bind() const;
	void Unbind() const;
	void Prepare();
	void Draw() const;

	const ProgramHandler& GetProgram() const { return m_Program; } 
	ProgramHandler& GetProgram() { return m_Program; }
	const VBOHandler& GetVBO() const { return m_VBO; }
	VBOHandler& GetVBO() { return m_VBO; }
	void AddModelTransform(const glm::mat4& value) { m_ModelTransforms.push_back(value); }

protected:
	virtual void GenerateGLObjectId() override;

private:
	ProgramHandler m_Program;
	TextureHandler m_Texture;
	VBOHandler m_VBO;
	EBOHandler m_EBO;
	std::vector<glm::mat4> m_ModelTransforms{};
	Camera* m_Camera;
	GLuint m_VAOId{0};
};
