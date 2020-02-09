#pragma once

#include "graphics/graphicsheader.h"

#include "graphics/mesh.h"
#include "graphics/texturehandler.h"

#include <assimp/material.h>

struct aiNode;
struct aiScene;
struct aiMesh;
struct aiMaterial;

using MeshPtr = std::unique_ptr<Mesh>;

class Model
{
public:
	void Load();
	void ProcessNode(const aiNode* node, const aiScene* scene);
	Mesh CreateMesh(const aiMesh* mesh, const aiScene* scene);

	void RegisterPosition(glm::mat4* position);
	void UnregisterPosition(glm::mat4* position);

	void SetFileName(const std::string& fileName) { m_FileName = fileName; }

private:
	std::string m_FileName{};
	std::vector<MeshPtr> m_Meshes{};
	std::vector<TextureHandler> m_TexturesLoaded{};

	std::vector<TextureHandler> LoadMaterialTextures(aiMaterial* material, aiTextureType type, const std::string& typeName);
};
