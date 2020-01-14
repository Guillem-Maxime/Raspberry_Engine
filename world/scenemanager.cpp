#include "world/scenemanager.h"

#include "world/entity.h"
#include "world/components/graphiccomponent.h"

void SceneManager::OnEngineStart()
{
	LoadStaticEntities();
	LoadSavedEntities();
	for(auto& e : m_Entities)
	{
		e->Create();
	}
}

void SceneManager::OnUpdate()
{
	UpdateEntities();
}

void SceneManager::OnEngineStop()
{
	DestroyEntities();
}

void SceneManager::UpdateEntities()
{
	for(auto& e : m_Entities)
	{
		e->Update();
	}
}

void SceneManager::LoadStaticEntities()
{
	m_Entities.emplace_back(std::make_unique<Entity>());
	Entity* earthEntity{ m_Entities.back().get() };
	
	GraphicComponent* graphicComponent{ earthEntity->RegisterComponent<GraphicComponent>() };
	graphicComponent->SetPath("model/earth.usdz");
}

void SceneManager::LoadSavedEntities()
{

}

void SceneManager::DestroyEntities()
{
	for(auto& e : m_Entities)
	{
		e->Destroy();
		e.reset();
	}
	m_Entities.clear();
}
