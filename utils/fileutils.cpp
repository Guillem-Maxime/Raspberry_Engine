#include "fileutils.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "graphics/mesh.h"
#include "graphics/openglrendermanager.h"
#include "graphics/texturehandler.h"

#include "ext/stb_image.h"
#include "graphics/graphicsheader.h"

namespace FileUtils
{
	void ReadFile(const std::string& fileName, std::string& outString)
	{
		outString.clear();
		std::ifstream istr(fileName, std::ios_base::ate);
		if(istr.is_open())
		{
			istr.clear();
			istr.seekg(0, std::ios_base::beg);
			std::stringstream sstr;
			sstr << istr.rdbuf();
			istr.close();
			outString = sstr.str();
			std::cout << "READING::FILE::" << fileName << std::endl;
		}
		else
		{
			std::cerr << "UNABLE TO READ FILE : " << fileName << std::endl;
		}
	}

	unsigned char* LoadTexture(const char* fileName, ImageInfos& infos)
	{
		stbi_set_flip_vertically_on_load(true);
		EFileType fileType = GetFileTypeFromExtension(fileName);
		
		std::cout << "LOADING::TEXTURE::" << fileName << std::endl;

		switch(fileType)
		{
			case EFileType::JPG:
			case EFileType::JPEG:
				infos.m_ColorChannel = GL_RGB;
				break;
			case EFileType::PNG:
				infos.m_ColorChannel = GL_RGBA;
				break;
			case EFileType::Unknown:
			default:
				std::cerr << "ERROR::FILE:EXTENSION:NOT:FOUND";
		}
		return stbi_load(fileName, &infos.m_Width, &infos.m_Height, &infos.m_NbrChannels, 0);
	}

	EFileType GetFileTypeFromExtension(const char* fileName)
	{
		const std::string strFileName{ fileName };
		return GetFileTypeFromExtension(strFileName);
	}

	EFileType GetFileTypeFromExtension(const std::string& strFileName)
	{
		size_t pos{ strFileName.find(".") };
		if( pos == std::string::npos)
		{
			std::cerr << "ERROR this file " << strFileName << " has no extension !" << std::endl;
			return EFileType::Unknown;
		}

		const std::string extension{ strFileName.substr(pos, strFileName.size()) };
		if( extension == ".jpg" )
		{
			return EFileType::JPG;
		}
		else if( extension == ".jpeg" ) 
		{
			return EFileType::JPEG;
		}
		else if( extension == ".png" ) 
		{
			return EFileType::PNG;
		}
		else if( extension == ".obj" )
		{
			return EFileType::OBJ;
		}
		else
		{
			return EFileType::Unknown;
		}
	}

	void Load3DModel(const std::string& fileName, std::vector<Mesh>& outMeshes)
	{
		const EFileType fileType{ GetFileTypeFromExtension(fileName) };
		switch(fileType)
		{
			case EFileType::OBJ :
				Load3DObjModel(fileName, outMeshes);
				break;
			default:
				Load3DDefaultModel(fileName, outMeshes);
				break;
		}
	}

	void Load3DObjModel(const std::string& fileName, std::vector<Mesh>& outMeshes)
	{

	}

	void Load3DDefaultModel(const std::string& fileName, std::vector<Mesh>& outMeshes)
	{
		Assimp::Importer importer;
		aiScene* scene{ importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs) };
		if(scene != nullptr)
		{
			ProcessNode(scene->mRootNode, scene);
			for(const auto& mesh : outMeshes)
			{
				OpenGLRenderManager::Get()->RegisterToRender(mesh.get());
			}
		}
		else
		{
			std::cerr << "ERROR::NO:3D:MODEL:LOADED" << std::endl;
		}
	}

	void ProcessNode(const aiNode* node, const aiScene* scene, std::vector<Mesh>& outMeshes)
	{
		if(scene == nullptr)
			std::cout << "scene should not be nullptr here" << std::endl;
		if(node == nullptr)
			std::cout << "node should not be nullptr here" << std::endl;
		for(unsigned int i{0}; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh{ scene->mMeshes[node->mMeshes[i]] };
			outMeshes.push_back(std::make_unique<Mesh>(CreateMesh(mesh, scene)) );
		}
		for(unsigned int i{0}; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	//temp
	Mesh CreateMesh(const aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex1P1N1U> vertices;
		vertices.reserve(mesh->mNumVertices);
		std::vector<unsigned int> indices;
		std::vector<TextureHandler> textures;

		for(unsigned int i{ 0 }; i < mesh->mNumVertices; i++)
		{
			Vertex1P1N1U vertex;
			glm::vec3 vector;
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.m_Position = vector;

			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.m_Normal = vector;
		
			if(mesh->mTextureCoords[0])
			{
				glm::vec2 vec;
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.m_Texture = vec;
			}
			else
			{
				vertex.m_Texture = glm::vec2(0.0f, 0.0f);
			}
			vertices.push_back(vertex);
		}

		for(unsigned int i{ 0 }; i < mesh->mNumFaces ; i++)
		{
			aiFace face{ mesh->mFaces[1] };
			for(unsigned int j{ 0 }; i < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[i]);
			}
		}

		if(mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material{ scene->mMaterials[mesh->mMaterialIndex] };
			std::vector<TextureHandler> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());	
			std::vector<TextureHandler> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());	
		}

		Mesh result;
		result.SetVertices(vertices);
		result.SetIndices(indices);
		result.SetTextures(textures);
		return result;
	}

	std::vector<TextureHandler> Model::LoadMaterialTextures(aiMaterial* material, aiTextureType type, const std::string& typeName)
	{
		std::vector<TextureHandler> result;
		for(unsigned int i{ 0 }; i < material->GetTextureCount(type); i++)
		{
			aiString str;
			material->GetTexture(type, i, &str);
			bool skip{false};
			for(const auto& tex : m_TexturesLoaded)
			{
				if(std::strcmp(tex.GetFile().c_str(), str.C_Str()) == 0)
				{
					result.push_back(tex);
					skip = true;
					break;
				}
			}
			if(!skip)
			{
				TextureHandler texture;
				texture.SetTextureAiType(typeName);
				result.push_back(texture);
				m_TexturesLoaded.push_back(texture);
			}
		}
		return result;
	}
} //FileUtils
