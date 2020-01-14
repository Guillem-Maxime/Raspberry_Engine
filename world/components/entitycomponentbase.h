#pragma once

class Entity;

class EntityComponentBase
{
public:
	virtual ~EntityComponentBase() {}

	virtual void OnEntityCreate() {}
	virtual void Update() {}
	virtual void OnEntityDestroy() {}

	inline void SetOwner(Entity* value) { m_Owner = value; }
	inline const Entity* GetOwner() const { return m_Owner; }
	inline Entity* GetOwner() { return m_Owner; }
private:
	Entity* m_Owner{nullptr};
};
