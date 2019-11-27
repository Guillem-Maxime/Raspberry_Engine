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
	GLenum GetUnit() constexpr;
	virtual T* GetRaw() constexpr = 0;
	virtual GLuint Getsize() constexpr = 0;
	virtual void GetAttribPointerInfo(std::vector<AttribPointerInfo>& outAttribPointerInfos) const = 0;

};

template<typename T>
GLenum VertexBase<T>::GetUnit() constexpr
{
	return GL_NONE;
}

template<>
GLenum VertexBase<GLfloat>::GetUnit() constexpr
{
	return GL_FLOAT;
}

struct Vertex1P1N1U : VertexBase<GLfloat>
{
	glm::vec3 m_Position{ 0.0f, 0.0f, 0.0f };
	glm::vec3 m_Normal{ 0.0f, 0.0f, 0.0f };
	glm::vec2 m_Texture{ 0.0f, 0.0f };

	virtual GLfloat* GetRaw() constexpr override;
	virtual GLuint GetSize() constexpr override;
	virtual void GetAttribPointerInfo(std::vector<AttribPointerInfo>& outAttribPointerInfos) const override;
};

GLfloat* Vertex1P1N1U::GetRaw() constexpr
{
	return {  {m_Position.x, m_Position.y, m_Position.z}
			, {m_Normal.x, m_Normal.y, m_Normal.z}
			, {m_Texture.x, m_Texture.y} };
}

GLuint Vertex1P1N1U::GetSize() constexpr
{
	return 8 * sizeof(GLfloat);
}

void Vertex1P1N1U::GetAttribPointerInfo(std::vector<AttribPointerInfo>& outAttribPointerInfos) const
{
	outAttribPointerInfos.clear();
	outAttribPointerInfos.reserve(3);
	{
		AttribPointerInfo positionInfo;
		positionInfo.m_Position = 0;
		positionInfo.m_Size = 3;
		positionInfo.m_Stride = 8 * sizeof(GLfloat);
		positionInfo.m_Offset = 0;
		outAttribPointerInfos.push_back(positionInfo);
	}
	{
		AttribPointerInfo normalInfo;
		normalInfo.m_Position = 1;
		normalInfo.m_Size = 3;
		normalInfo.m_Stride = 8 * sizeof(GLfloat);
		normalInfo.m_Offset = 3 * sizeof(GLfloat);
		outAttribPointerInfos.push_back(normalInfo);
	}
	{
		AttribPointerInfo textureInfo;
		textureInfo.m_Position = 2;
		textureInfo.m_Size = 2;
		textureInfo.m_Stride = 8 * sizeof(GLfloat);
		textureInfo.m_Offset = 6 * sizeof(GLfloat);
		outAttribPointerInfos.push_back(textureInfo);
	}
}
