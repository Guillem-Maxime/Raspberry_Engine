#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include "graphics/mesh.h"

struct aiMaterial;
struct aiMesh;
struct aiNode;
struct aiScene;

namespace FileUtils
{
	enum class EFileType
	{
		JPG,
		JPEG,
		PNG,
		OBJ,
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
	EFileType GetFileTypeFromExtension(const std::string& strFileName);

	void Load3DModel(const std::string& fileName, std::vector<std::unique_ptr<Mesh>>& outMesh, std::vector<TextureHandler>& outTextures);
} //FileUtils
