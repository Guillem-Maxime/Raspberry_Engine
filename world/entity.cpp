#include "world/entity.h"

#include "world/components/entitycomponentbase.h"

void Entity::Create()
{
	CreateComponents();
}

void Entity::Update()
{
	UpdateComponents();
}

void Entity::Destroy()
{
	DestroyComponents();
}

void Entity::CreateComponents()
{
	for(auto& c : m_Components)
	{
		c->OnEntityCreate();
	}
}

void Entity::DestroyComponents()
{
	for(auto& c : m_Components)
	{
		c->OnEntityDestroy();
		c.reset();
	}
	m_Components.clear();
}

void Entity::UpdateComponents()
{
	for(auto& c : m_Components)
	{
		c->Update();
	}
}
