#include "engine/engine.h"

#include "engine/enginecomponent.h"
#include "graphics/openglrendermanager.h"
#include "world/scenemanager.h"


void Engine::Create()
{
	RegisterComponent<OpenGLRenderManager>();
	RegisterComponent<SceneManager>();
	for(const auto* c : m_Components)
	{
		std::cout << c->GetName() << " Registered" << std::endl;
	}
}

void Engine::Init()
{
	for(int i{ 0 } ; i < static_cast<int>(m_Components.size()) ; i++)
	{
		m_Components[i]->OnInit();
	}
}

void Engine::Start()
{
	for(int i{ 0 } ; i < static_cast<int>(m_Components.size()) ; i++)
	{
		m_Components[i]->OnEngineStart();
	}
}

void Engine::Update()
{
	for(int i{ 0 } ; i < static_cast<int>(m_Components.size()) ; i++)
	{
		m_Components[i]->OnUpdate();
	}
}

void Engine::Stop()
{
	for(int i{ static_cast<int>(m_Components.size()) -1 } ; i >= 0 ; i--)
	{
		m_Components[i]->OnEngineStop();
	}
}

void Engine::Shutdown()
{
	for(int i{ static_cast<int>(m_Components.size()) -1 } ; i >= 0 ; i--)
	{
		m_Components[i]->OnShutdown();
	}
}

void Engine::Delete()
{
	UnregisterComponent<OpenGLRenderManager>();
	m_Components.clear();
}

