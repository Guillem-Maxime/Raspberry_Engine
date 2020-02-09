#include "world/scenemanager.h"

#include "world/entity.h"
#include "world/components/graphiccomponent.h"

void SceneManager::OnEngineStart()
{
	LoadStaticEntities();
	LoadSavedEntities();
	std::cout << "Entities number : " << m_Entities.size() << std::endl;
	for(auto& e : m_Entities)
	{
		e->Create();
	}
	std::cout << "After entities created" << std::endl;
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
	std::cout << "Update entities" << std::endl;
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
	graphicComponent->SetPath("model/test.obj");
	std::cout << "Entities number : " << m_Entities.size() << std::endl; 
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
