#include "world/components/graphiccomponent.h"

#include "graphics/model.h"
#include "graphics/modelmanager.h"
#include "world/entity.h"

void GraphicComponent::OnEntityCreate()
{
	m_Model = ModelManager::Get()->RegisterModel(m_ModelPath);
	if(m_Model != nullptr)
	{
		m_Model->RegisterPosition(&GetOwner()->GetPosition());
	}
}

void GraphicComponent::OnEntityDestroy()
{
	if(m_Model != nullptr)
	{
		m_Model->UnregisterPosition(&GetOwner()->GetPosition());
		ModelManager::Get()->UnregisterModel(m_ModelPath);
		m_Model = nullptr;
	}
}
