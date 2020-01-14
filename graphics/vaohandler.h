#pragma once

#include "graphicsheader.h"

#include "ebohandler.h"
#include "programhandler.h"
#include "openglobjecthandler.h"
#include "texturehandler.h"
#include "vbohandler.h"

class Camera;
class Mesh;

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
	void Shutdown();
	void Bind() const;
	void Unbind() const;
	void Prepare();
	void Draw() const;
	
	inline const ProgramHandler& GetProgram() const { return m_Program; } 
	inline ProgramHandler& GetProgram() { return m_Program; }
	
	inline const VBOHandler& GetVBO() const { return m_VBO; }
	inline VBOHandler& GetVBO() { return m_VBO; }
	
	inline Mesh* GetMesh() { return m_Mesh; }
	inline const Mesh* GetMesh() const { return m_Mesh; }
	inline void SetMesh(Mesh* value) { m_Mesh = value; }

	void RegisterPosition(glm::mat4* position);
	void UnregisterPosition(glm::mat4* position);

protected:
	virtual void GenerateGLObjectId() override;

private:
	ProgramHandler m_Program;
	TextureHandler m_Texture;
	VBOHandler m_VBO;
	EBOHandler m_EBO;
	std::vector<glm::mat4*> m_ModelTransforms{};
	Camera* m_Camera;
	Mesh* m_Mesh;
	GLuint m_VAOId{0};
};
