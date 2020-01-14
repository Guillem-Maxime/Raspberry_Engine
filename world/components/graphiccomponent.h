#pragma once

#include "world/worldheaders.h"
#include "world/components/entitycomponentbase.h"

class Model;

class GraphicComponent : public EntityComponentBase
{
public:
	virtual void OnEntityCreate() override;
	virtual void OnEntityDestroy() override;

	inline void SetPath(const std::string& value) { m_ModelPath = value; }
private:
	Model* m_Model{ nullptr };
	std::string m_ModelPath;
};
