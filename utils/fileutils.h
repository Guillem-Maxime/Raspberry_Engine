#pragma once

#include <string>

struct aiScene;

namespace FileUtils
{
	enum class EFileType
	{
		JPG,
		JPEG,
		PNG,
		Unknown
	};

	struct ImageInfos
	{
		int m_Width{ 0 };
		int m_Height{ 0 };
		int m_NbrChannels{ 0 };	
		int m_ColorChannel{ 0 };
	};

	void ReadFile(const std::string& fileName, std::string& outString);
	
	unsigned char* LoadTexture(const char* fileName, ImageInfos& outInfos);
	EFileType GetFileTypeFromExtension(const char* fileName);

	const aiScene* Load3DModel(const std::string& fileName);
} //FileUtils
