#pragma once

#include "common/commonheaders.h"
#include "common/singleton.h"
#include "engine/enginecomponent.h"
#include "graphics/vaohandler.h"

using VAOPtr = std::unique_ptr<VAOHandler>;

class OpenGLRenderManager : public EngineComponent, public Singleton<OpenGLRenderManager>
{
public:
	virtual ~OpenGLRenderManager() {}

	virtual void OnInit() override;
	virtual void OnEngineStart() override;
	virtual void OnUpdate() override;
	virtual void OnShutdown() override;

	virtual std::string GetName() const override { return "OpenGLRenderManager";}
	void RegisterToRender(Mesh* mesh);

private:
	using super = EngineComponent;

	std::vector<VAOPtr> m_VAOs{};
	int m_WindowId{ 0 };
};
