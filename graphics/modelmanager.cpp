#include "graphics/modelmanager.h"

void ModelManager::OnShutdown()
{
	for(auto& m : m_Models)
	{
		DestroyModel(m.second);
	}
	m_Models.clear();
}

Model* ModelManager::RegisterModel(const std::string& path)
{
	Model* model{nullptr};
	auto it{ m_Models.find(path) };
	if(it != m_Models.end())
	{
		ModelHandler& modelHandler = it->second;
		modelHandler.m_Count++;
		model = modelHandler.m_Model.get();
	}
	else
	{
		model = CreateModel(path);
	}
	return model;
}

void ModelManager::UnregisterModel(const std::string& path)
{
	auto it{ m_Models.find(path) };
	if(it != m_Models.end())
	{
		ModelHandler& modelHandler{ it->second }; 
		modelHandler.m_Count--;
		if(modelHandler.m_Count <= 0)
		{
			m_Models.erase(it);
		}
	}
	else
	{
		std::cerr << "ERROR::TRYING_TO_UNREGISTER_INEXISTANT_MODEL" << std::endl;
	}
}

Model* ModelManager::CreateModel(const std::string& path)
{
	ModelHandler modelHandler;
	modelHandler.m_Model = std::make_unique<Model>();
	modelHandler.m_Count++;
	modelHandler.m_Path = path;

	m_Models[path] = std::move(modelHandler);
	return m_Models[path].m_Model.get();
}

void ModelManager::DestroyModel(ModelHandler& modelHandler)
{
	modelHandler.m_Model.reset();
	modelHandler.m_Count = 0;
	modelHandler.m_Path = "";
}
