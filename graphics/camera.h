#pragma once

#include "graphicsheader.h"

class Camera
{
public:
	Camera() = default;
	virtual ~Camera() = default;

	void Init();
	inline void SetProjectionMatrix(const glm::mat4& value) { m_ProjectionMatrix = value; }
	inline void SetViewMatrix(const glm::mat4& value) { m_ViewMatrix = value; }
	inline glm::mat4 GetViewProjMatrix() const { return glm::mat4(m_ProjectionMatrix * m_ViewMatrix); }
private:
	glm::mat4 m_ViewMatrix{ glm::mat4(1.0f) };
	glm::mat4 m_ProjectionMatrix{ glm::mat4(1.0f) };

	void ResetToDefault();	
};
