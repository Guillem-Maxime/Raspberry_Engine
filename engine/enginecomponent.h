#pragma once

#include "common/commonheaders.h"

class EngineComponent
{
public:
	virtual ~EngineComponent() {}

	virtual void OnInit() 
	{
		std::cout << "Init" << std::endl;
		std::cout << GetName() << " OnInit()" << std::endl;
	}

	virtual void OnEngineStart()
	{
		std::cout << GetName() << " OnEngineStart()" << std::endl;
	}
	virtual void OnUpdate()
	{
		std::cout << GetName() << " OnUpdate()" << std::endl;
	}

	virtual void OnEngineStop()
	{
		std::cout << GetName() << " OnEngineStop()" << std::endl;
	}

	virtual void OnShutdown()
	{
		std::cout << GetName() << " OnShutdown()" << std::endl;
	}

	virtual std::string GetName() const = 0;
};
