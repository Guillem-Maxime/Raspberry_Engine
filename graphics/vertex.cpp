#include "vertex.h"

void Vertex1P1N1U::GetAttribPointerInfos(std::vector<AttribPointerInfo>& outAttribPointerInfos)
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
		normalInfo.m_Offset = sizeof(glm::vec3);
		outAttribPointerInfos.push_back(normalInfo);
	}
	{
		AttribPointerInfo textureInfo;
		textureInfo.m_Position = 2;
		textureInfo.m_Size = 2;
		textureInfo.m_Stride = stride;
		textureInfo.m_Offset = sizeof(glm::vec3) + sizeof(glm::vec3);
		outAttribPointerInfos.push_back(textureInfo);
	}
}
