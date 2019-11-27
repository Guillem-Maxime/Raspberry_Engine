#pragma once

#include "graphicsheader.h"

struct AttribPointerInfo
{
	GLuint m_Position{0};
	GLuint m_Size{3};
	GLuint m_Stride{0};
	GLuint m_Offset{0};
};

template<typename T>
struct VertexBase
{
	constexpr GLenum GetUnit() const;
	virtual void GetAttribPointerInfo(std::vector<AttribPointerInfo>& outAttribPointerInfos) const = 0;
};

template<typename T>
constexpr GLenum VertexBase<T>::GetUnit() const
{
	return GL_NONE;
}

template<>
constexpr GLenum VertexBase<GLfloat>::GetUnit() const
{
	return GL_FLOAT;
}

struct Vertex1P1N1U : VertexBase<GLfloat>
{
	glm::vec3 m_Position{ 0.0f, 0.0f, 0.0f };
	glm::vec3 m_Normal{ 0.0f, 0.0f, 0.0f };
	glm::vec2 m_Texture{ 0.0f, 0.0f };

    virtual void GetAttribPointerInfo(std::vector<AttribPointerInfo>& outAttribPointerInfos) const override;    
};

