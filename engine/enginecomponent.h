#pragma once


class EngineComponent
{
public:
	virtual ~EngineComponent() {}

	virtual void OnInit() {}
	virtual void OnEngineStart() {}
	virtual void OnUpdate() {}
	virtual void OnEngineStop() {}
	virtual void OnShutdown() {}

	virtual std::string GetName() const = 0;
};
