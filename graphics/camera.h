#pragma once

#include "graphicsheader.h"

class Camera
{
public:
	Camera() = default;
	virtual ~Camera() = default;

	void Init();
	inline void SetProjectionMatrix(const glm::mat4& value) 
	{ 
		m_ProjectionMatrix = value; 
		UpdateProjView();
	}
	inline void SetViewMatrix(const glm::mat4& value) 
	{ 
		m_ViewMatrix = value; 
		UpdateProjView();
	}
	inline glm::mat4 GetProjViewMatrix() const { return m_ProjViewMatrix; }
private:
	glm::mat4 m_ViewMatrix{ glm::mat4(1.0f) };
	glm::mat4 m_ProjectionMatrix{ glm::mat4(1.0f) };
	glm::mat4 m_ProjViewMatrix{ glm::mat4(1.0f) };

	void ResetToDefault();
	void UpdateProjView();
};
