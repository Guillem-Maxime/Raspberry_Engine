#pragma once

#include "common/commonheaders.h"
#include "common/singleton.h"

class EngineComponent;

struct CommandLineArgs
{
	int m_Argc{ 0 };
	char** m_Argv{ nullptr };
};

class Engine : public Singleton<Engine>
{
public:
	virtual ~Engine() {}

	void Create();
	void Init();
	void Start();
	void Update();
	void Stop();
	void Shutdown();
	void Delete();
	
	inline void SetCommandArgs(const CommandLineArgs& args) { m_Args = args; }
	inline const CommandLineArgs& GetCommandArgs() const { return m_Args; }
	inline CommandLineArgs& GetCommandArgs() { return m_Args; }

protected:
	CommandLineArgs m_Args;
	std::vector<EngineComponent*> m_Components;

private:
	template<class T>
	void RegisterComponent()
	{
			T* component = T::Get();
			m_Components.push_back(component);
	}

	template<class T>
		void UnregisterComponent()
		{
			T::Destroy();
		}
};
