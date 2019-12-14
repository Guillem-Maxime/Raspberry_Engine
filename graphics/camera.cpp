#include "camera.h"

constexpr GLfloat CAMERA_POSITION_X{  0.0f };
constexpr GLfloat CAMERA_POSITION_Y{  0.0f };
constexpr GLfloat CAMERA_POSITION_Z{ -5.0f };

constexpr GLfloat PROJECTION_ANGLE{ 45.0f };
constexpr GLfloat SCREEN_RATIO{ 800.0f / 600.0f };
constexpr GLfloat FRUSTRUM_BEGIN{ 1.0f };
constexpr GLfloat FRUSTRUM_END{100.0f };

void Camera::Init()
{
	ResetToDefault();
}

void Camera::ResetToDefault()
{
	m_ViewMatrix = glm::mat4(1.0f);
	m_ViewMatrix = glm::translate(m_ViewMatrix, glm::vec3(CAMERA_POSITION_X, CAMERA_POSITION_Y, CAMERA_POSITION_Z));
	m_ProjectionMatrix = glm::mat4(1.0f);
	m_ProjectionMatrix = glm::perspective(glm::radians(PROJECTION_ANGLE), SCREEN_RATIO, FRUSTRUM_BEGIN, FRUSTRUM_END);
	UpdateProjView();
}

void Camera::UpdateProjView()
{
	m_ProjViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
}
