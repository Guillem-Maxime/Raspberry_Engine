#include "vaohandler.h"

#include "camera.h"
#include "glutils.h"

void VAOHandler::Init(const VAOInitializer& initializer)
{
	InitInternal();
	m_Program.Init(initializer.m_ProgramInitializer);
	Bind();
	m_Texture.Init(initializer.m_TextureInfos);
	m_VBO.Init(initializer.m_VBOInfos);
	m_EBO.Init(initializer.m_EBOInfos);
	m_Camera = initializer.m_Camera;
	if(m_Camera == nullptr)
	{
		std::cerr << "ERROR::CAMERA::MISSING::VAO::" << m_VAOId << std::endl;
	}
}

void VAOHandler::GenerateGLObjectId()
{
	glGenVertexArrays(1, &m_VAOId); 
}

void VAOHandler::Shutdown()
{
	m_Texture.Shutdown();
	m_Program.Shutdown();
	m_VBO.Shutdown();
	m_EBO.Shutdown();
	glDeleteVertexArrays(1, &m_VAOId);
}

void VAOHandler::Bind() const
{
	if(IsInitialized())
	{
		glBindVertexArray(m_VAOId);
		if(GLUtils::GetGLError("VAOBind"))
		{
			std::cerr << "\tID::" << m_VAOId << std::endl;
		}
	}
	else
	{
		std::cerr << "VAO Not Initialized ID : " << m_VAOId << std::endl;
	}
}

void VAOHandler::Unbind() const
{
	m_EBO.Unbind();
	m_VBO.Unbind();
	glBindVertexArray(0);
	if(GLUtils::GetGLError("VAOBind"))
	{
		std::cerr << "\tID::" << m_VAOId << std::endl;
	}
}

void VAOHandler::Prepare()
{
	m_Program.Link();
	Bind();
	m_VBO.Prepare();
	m_EBO.Prepare();
	m_Texture.Prepare();
	m_Program.AddTexture(&m_Texture);
}

void VAOHandler::Draw() const
{	
	m_Program.SetUniformVariable(m_Camera->GetProjViewMatrix(), "mProjView");
	for(const glm::mat4& modelTransform : m_ModelTransforms)
	{
		m_Program.SetUniformVariable(modelTransform, "mModel");
	
		m_Program.Use();
		GLUtils::GetGLError("Draw_UseProgram");
		Bind();
		GLUtils::GetGLError("Draw_Bind");
		m_EBO.Draw();
		GLUtils::GetGLError("Draw_VBO");
	}
}
