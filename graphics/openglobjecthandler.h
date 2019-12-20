#pragma once

class OpenGLObjectHandler
{
public:
	OpenGLObjectHandler() = default;
	virtual ~OpenGLObjectHandler() = default;
	OpenGLObjectHandler(const OpenGLObjectHandler&) = default;

protected:
	inline bool IsInitialized() const { return m_IsInitialized; }
	void InitInternal();
	virtual void GenerateGLObjectId() = 0;

private:
	bool m_IsInitialized{false};
};
