#pragma once

#include "common/commonheaders.h"
#include "common/singleton.h"
#include "engine/enginecomponent.h"
#include "graphics/model.h"

struct ModelHandler
{
	std::unique_ptr<Model> m_Model;
	unsigned int m_Count{ 0 };
	std::string m_Path;
};

class ModelManager : public EngineComponent, public Singleton<ModelManager>
{
public:
	virtual ~ModelManager() {}
	virtual void OnShutdown() override;

	Model* RegisterModel(const std::string& path);
	void UnregisterModel(const std::string& path);

	virtual std::string GetName() const override { return "ModelManager"; }

private:
	std::map<std::string, ModelHandler> m_Models{};

	Model* CreateModel(const std::string& path);
	void DestroyModel(ModelHandler& modelHandler);
};
