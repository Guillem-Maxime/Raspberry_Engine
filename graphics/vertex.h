#pragma once

#include "graphicsheader.h"

struct AttribPointerInfo
{
	GLuint m_Position{0};
	GLuint m_Size{3};
	size_t m_Stride{0};
	size_t m_Offset{0};
};

struct Vertex1P1N1U
{
	glm::vec4 m_Position{ 0.0f, 0.0f, 0.0f, 0.0f };
	glm::vec3 m_Normal{ 0.0f, 0.0f, 0.0f };
	glm::vec2 m_Texture{ 0.0f, 0.0f };

    static void GetAttribPointerInfos(std::vector<AttribPointerInfo>& outAttribPointerInfos);    
};

