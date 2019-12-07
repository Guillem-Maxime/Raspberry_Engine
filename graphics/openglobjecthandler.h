#pragma once

class OpenGLObjectHandler
{
public:
	virtual ~OpenGLObjectHandler() = default;

protected:
	inline bool IsInitialized() const { return m_IsInitialized; }
	void InitInternal() 
	{ 
		m_IsInitialized = true; 
		GenerateGLObjectId();
	}
	virtual void GenerateGLObjectId() = 0;

private:
	bool m_IsInitialized{false};
};
