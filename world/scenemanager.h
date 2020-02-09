#pragma once

#include "common/singleton.h"
#include "engine/enginecomponent.h"
#include "world/entity.h"
#include "world/worldheaders.h"

using EntityPtr = std::unique_ptr<Entity>;

class SceneManager : public EngineComponent, public Singleton<SceneManager>
{
public:
	virtual ~SceneManager() override {}
	
	virtual void OnEngineStart() override;
	virtual void OnUpdate() override;
	virtual void OnEngineStop() override;

	virtual std::string GetName() const override { return "SceneManager"; }

private:
	std::vector<EntityPtr> m_Entities{};

	void LoadSavedEntities();
	void LoadStaticEntities();
	void UpdateEntities();
	void DestroyEntities();
};
