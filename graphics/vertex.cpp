#include "vertex.h"

void Vertex1P1N1U::GetAttribPointerInfo(std::vector<AttribPointerInfo>& outAttribPointerInfos) const
{
    outAttribPointerInfos.clear();
	outAttribPointerInfos.reserve(3);
    const GLuint stride{sizeof(Vertex1P1N1U)};
	{
		AttribPointerInfo positionInfo;
		positionInfo.m_Position = 0;
		positionInfo.m_Size = 3;
		positionInfo.m_Stride = stride;
		positionInfo.m_Offset = 0;
		outAttribPointerInfos.push_back(positionInfo);
	}
	{
		AttribPointerInfo normalInfo;
		normalInfo.m_Position = 1;
		normalInfo.m_Size = 3;
		normalInfo.m_Stride = stride;
		normalInfo.m_Offset = 3 * sizeof(GLfloat);
		outAttribPointerInfos.push_back(normalInfo);
	}
	{
		AttribPointerInfo textureInfo;
		textureInfo.m_Position = 2;
		textureInfo.m_Size = 2;
		textureInfo.m_Stride = stride;
		textureInfo.m_Offset = 6 * sizeof(GLfloat);
		outAttribPointerInfos.push_back(textureInfo);
	}
}
