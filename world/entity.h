#pragma once

#include "world/worldheaders.h"
#include "world/components/entitycomponentbase.h"

using ComponentPtr = std::unique_ptr<EntityComponentBase>;

class Entity
{
public:
	void Create();
	void Update();
	void Destroy();
	inline const glm::mat4& GetPosition() const { return m_Position; }  
	inline glm::mat4& GetPosition() { return m_Position; }

	template<class T>
	T* RegisterComponent()
	{
		m_Components.emplace_back(std::make_unique<T>());
		auto component{ m_Components.back().get() };
		component->SetOwner(this);
		return static_cast<T*>(component);
	}
	
	
private:
	std::vector<ComponentPtr> m_Components{};
	glm::mat4 m_Position{ glm::mat4(1.0f) };

	EntityComponentBase* RegisterComponent();
	void CreateComponents();
	void UpdateComponents();
	void DestroyComponents();
};
