#include "graphics/openglrendermanager.h"

#include "engine/engine.h"
#include "graphics/graphicsheader.h"
#include "graphics/vaohandler.h"

void OpenGLRenderManager::OnInit()
{
	super::OnInit();
	CommandLineArgs& args{ Engine::Get()->GetCommandArgs() };
	glutInit(&args.m_Argc, args.m_Argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	std::cout << "OpenGLRenderManager OnInit()";
}

void OpenGLRenderManager::OnEngineStart()
{
	super::OnEngineStart();
	std::cout << "OpenGLRenderManager" << "OnEngineStart" << std::endl;
	m_WindowId = glutCreateWindow("Hello Window");
	if(glewInit())
	{
		std::cerr << "Unable to Initialize glew" << std::endl;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OpenGLRenderManager::OnUpdate()
{
	for(const auto& vao : m_VAOs)
	{
		vao.get()->Draw();
	}
}

void OpenGLRenderManager::OnShutdown()
{
	glutDestroyWindow( m_WindowId );
	super::OnShutdown();
}

void OpenGLRenderManager::RegisterToRender(Mesh* mesh)
{
	const auto closure = [mesh](const VAOPtr& vao){ return mesh == vao.get()->GetMesh(); };
	const auto findIt{ std::find_if(m_VAOs.begin(), m_VAOs.end(), closure) };
	if(findIt == m_VAOs.end())
	{
		VAOPtr& newVAO{ m_VAOs.emplace_back(std::make_unique<VAOHandler>()) };
		VAOHandler* vao = newVAO.get();
		mesh->SetVAO(vao);
		vao->SetMesh(mesh);
	}
	else
	{
		mesh->SetVAO(findIt->get());
	}
}
