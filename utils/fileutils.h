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

	const aiScene* Load3DModel(const std::string& fileName);

	void Load3DObjModel(const std::string& fileName, std::vector<Mesh>& outMeshes);
	void Load3DDefaultModel(const std::string& fileName, std::vector<Mesh>& outMeshes);
	void ProcessNode(const aiNode* node, const aiScene* scene, std::vector<Mesh>& outMeshes);
	Mesh CreateMesh(const aiMesh* mesh, const aiScene* scene);
	std::vector<TextureHandler> LoadMaterialTextures(aiMaterial* material, aiTextureType type, const std::string& typeName);

} //FileUtils
