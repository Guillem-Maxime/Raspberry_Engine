#include "model.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "graphics/openglrendermanager.h"

#include "utils/fileutils.h"

void Model::Load()
{
	const aiScene* scene{ FileUtils::Load3DModel(m_FileName) };
	if(scene != nullptr)
	{
		ProcessNode(scene->mRootNode, scene);
		for(const auto& mesh : m_Meshes)
		{
			OpenGLRenderManager::Get()->RegisterToRender(mesh.get());
		}
	}
	else
	{
		std::cerr << "ERROR::NO:3D:MODEL:LOADED" << std::endl;
	}
}

void Model::ProcessNode(const aiNode* node, const aiScene* scene)
{
	if(scene == nullptr)
		std::cout << "scene should not be nullptr here" << std::endl;
	if(node == nullptr)
		std::cout << "node should not be nullptr here" << std::endl;
	for(unsigned int i{0}; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh{ scene->mMeshes[node->mMeshes[i]] };
		m_Meshes.push_back(std::make_unique<Mesh>(CreateMesh(mesh, scene)) );
	}
	for(unsigned int i{0}; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

//temp
Mesh Model::CreateMesh(const aiMesh* mesh, const aiScene* scene)
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

void Model::RegisterPosition(glm::mat4* position)
{
	for(auto& m : m_Meshes)
	{
		m->RegisterPosition(position);
	}
}

void Model::UnregisterPosition(glm::mat4* position)
{
	for(auto& m : m_Meshes)
	{
		m->UnregisterPosition(position);
	}
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
